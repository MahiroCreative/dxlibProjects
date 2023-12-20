#include <DxLib.h>
#include <cassert>
#include "../util/Pad.h"
#include "../util/Rect.h"
#include "SceneMain.h"
#include "../Player.h"
#include "../Bg.h"
#include "../enemy/EnemyLeft.h"
#include "../enemy/EnemyRight.h"
#include "../enemy/EnemyToPlayer.h"
#include "../shot/ShotMagicWand.h"

namespace
{
	// 一度に登場できる敵の最大数
	constexpr int kEnemyMax = 32;
	// 何フレームおきに敵が登場するか
	constexpr int kEnemyInterval = 40;

	// 一度に搭乗できる弾の最大数
	constexpr int kShotMax = 256;

	// 画面がワイプするのにかかるフレーム数
	constexpr int kWipeFrame = 30;
}

SceneMain::SceneMain() :
	m_enemyInterval(0),
	m_wipeFrame(0),
	m_shakeFrame(0)
{
	// ゲーム画面描画先の設定
	// 画面サイズと同じ大きさのグラフィックデータを作成する
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// グラフィックのロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{this};
	m_pPlayer->SetHandle(m_playerHandle);

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);

	// 敵の準備
	// m_pEnemy(vector)何もしなければサイズは0

	// resize関数でkEnemyMaxだけデータを保存できるようにする
	m_pEnemy.resize(kEnemyMax);

	// いつもはコンストラクタでメモリを確保して
	// デストラクタで解放してください
	// 今回はランダムにEnemyLeft, EnemyRight, EnemyToPlayerを確保したい
	// どれか分からないのであらかじめ確保することができない！
	// →動的にメモリを確保する Update()中に必要に応じて

	// 初期状態ではメモリを確保していないことが分かるように
	// 未使用状態にする nullptrを入れておく
	// size()で現在使用可能な要素数を取得可能
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;
	}

	// ショットのメモリ確保
	m_pShot.resize(kShotMax);
	for (auto& shot : m_pShot)
	{
		shot = nullptr;
	}
}

SceneMain::~SceneMain()
{
	// MakeScreenで生成したグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);

	// メモリからグラフィックの削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

	// メモリが確保されている敵を探して解放していく
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;	// 未使用状態と分かるようにしておく
		}
	}

	// ショットのメモリ解放
	for (auto& shot : m_pShot)
	{
		if (!shot) continue;
		delete shot;
		shot = nullptr;
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();

	m_pBg->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pBg->Update();

	Rect playerRect = m_pPlayer->GetColRect();

	for (auto& enemy : m_pEnemy)
	{
		if (enemy)	// nullptrではないチェック : nullptrでない(何かかが入っている)なら動作
		{
			enemy->Update();

			// 使用済みの敵キャラクーを削除する必要がある
			if (!enemy->IsExist())
			{
				// メモリを解放する
				delete enemy;
				enemy = nullptr;	// 使っていないと分かるように
			}
			// 存在している敵とプレイヤーと当たり判定
			else if ( playerRect.IsCollsion(enemy->GetColRect()) )
			{
				m_pPlayer->OnDamage();
				// プレイヤーがダメージを受けた瞬間、画面が揺れ始める
				m_shakeFrame = 8;
			}
		}
	}

	for (auto& shot : m_pShot)
	{
		if (!shot)	continue;

		shot->Update();

		if (!shot->IsExist())
		{
			delete shot;
			shot = nullptr;

			continue;
		}

		// 敵と弾との当たり判定
		// 現状はどの弾が当たっても
		// 両方消える
		/*Rect shotRect = shot->GetColRect();

		for (auto& enemy : m_pEnemy)
		{
			if (!enemy) continue;

			if (shotRect.IsCollsion(enemy->GetColRect()))
			{
				delete shot;
				shot = nullptr;

				delete enemy;
				enemy = nullptr;

				break;
			}
		}*/
	}

	// 敵キャラクターを登場させる
	// kEnemyIntevalフレーム経過するごとにランダムに敵を登場させる
	m_enemyInterval++;
	if (kEnemyInterval <= m_enemyInterval)
	{
		m_enemyInterval = 0;

		switch (GetRand(2))
		{
		case 0:	// Letf
			CreateEnemyLeft();
			break;
		case 1:	// Right
			CreateEnemyRight();
			break;

			// 小テク
		default:	assert(false); // breakなし
		case 2:	// ToPlayer
			CreateEnemyToPlayer();
			break;
		}
	}

	// ワイプ処理
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame) m_wipeFrame = kWipeFrame;

	// 揺れ処理
	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
	}
}

void SceneMain::Draw() const
{
	// バックバッファに直接書き込むのではなく
	// 自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBg->Draw();
	m_pPlayer->Draw();
	for (const auto& enemy : m_pEnemy)
	{
		if (enemy)	// nullptrではないチェック
		{
			enemy->Draw();
		}
	}

	for (const auto& shot : m_pShot)
	{
		if (!shot)	continue;
		shot->Draw();
	}

	// デバック表示
	DrawString(8, 8, "SceneMain", 0xffffff);

	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, 0xffffff, 
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
	int shotCount = 0;
	for (const auto& shot : m_pShot)
		if (shot) shotCount++;
	DrawFormatString(8, 40, 0xffffff, 
		"弾の数 %d", shotCount);

	// バッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;

	if (m_shakeFrame > 0)
	{
		screenX = GetRand(8) - 4;
		screenY = GetRand(8) - 4;
	}

	// m_wipeFrameから描画する範囲を計算する
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
	int wipeHeight = static_cast<int>(Game::kScreenHeight * wipeRate);

	//DrawRectGraph(screenX, screenY, 
	//	0, 0, Game::kScreenWidth, wipeHeight,
	//	m_gameScreenHandle, true, false);

	int offset = 320 * (1.0f - wipeRate);

	// 画面の上から1ラインずつ描画を行っている
	for (int y = 0; y < Game::kScreenHeight; y++)
	{
		int x = sinf(y * 0.05f) * offset;

		DrawRectGraph(x, y, 
			0, y, Game::kScreenWidth, 1,
		m_gameScreenHandle, true, false);
	}
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) const
{
	// 敵がいない場合は適当な座標を返す
	Vec2 result{ 0, 0 };
	// 最初の敵チェック済みフラグ
	bool isFirst = true;

	clsDx();
	// 一番近い敵キャラクターの座標をresultに入れる
	for (const auto& enemy : m_pEnemy)
	{
		// 使われていない敵はチェックしない
		if (!enemy) continue;
		// 範囲外の敵はチェックしない
		if (!enemy->IsExist()) continue;

		// posとenemyの距離をチェックする
		if (isFirst)
		{
			// 1体目の敵
			result = enemy->GetPos();
			isFirst = false;
		}
		else
		{
			// 2体目以降の敵
			// resultの中には一番近い敵の座標が入っている

			// 一番敵なら情報を更新
			if ((enemy->GetPos() - pos).SqLength() < (result - pos).SqLength())
			{
				result = enemy->GetPos();
			}
		}
	}

	// すべての敵のチェックを行ったのでこいつが1位で確定
	return result;
}

bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptrを渡されたら止まる
	assert(pShot);

	for (auto& shot : m_pShot)
	{
		if (shot)	continue;
		shot = pShot;
		// 登録したら終了
		return true;
	}

	// ここに来たという事はm_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

void SceneMain::CreateEnemyLeft()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptrであるチェック
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;// 一体分確保できたら終了
		}
	}
}

void SceneMain::CreateEnemyRight()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;
		}
	}
}

void SceneMain::CreateEnemyToPlayer()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			// Baseが持たない独自の関数を呼びたい
			EnemyToPlayer* pEnemy = new EnemyToPlayer;

			pEnemy->Init();
			pEnemy->SetHandle(m_enemyHandle);
			pEnemy->SetPlayer(m_pPlayer);	// pEnemyはEnemyToPlayerなので呼べる
			pEnemy->Start();

			// pEnemyはすぐ消えるのでm_pEnemyに確保したアドレスをコピーしておく
			m_pEnemy[i] = pEnemy;

			return;
		}
	}
}

