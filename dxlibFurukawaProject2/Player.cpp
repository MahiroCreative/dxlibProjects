#include <DxLib.h>
#include "Game.h"
#include "Pad.h"
#include "SceneMain.h"

#include "Player.h"

#include "ShotMagicWand.h"
#include "ShotBible.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 3.0f;

	// キャラクターのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
	// 半分のサイズ
	constexpr float kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr float kGraphHalfHeight = kGraphHeight / 2.0f;

	// キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 1 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 12;
	// アニメーションの１サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
									// _countof()で配列のサイズを取得できる
									// _countof(kUseFrame)

	// 魔法の杖の発射間隔
	constexpr int kMagicWandFrame = 30;

	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_walkAnimFrame(kAnimFrameNum),
	m_magicWandFrame(0),
	m_damageFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	// ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	bool isMove = false;	// 移動中かどうか

	// 移動量を持つようにする
	Vec2 move{ 0.0f, 0.0f };	// 引数ありコンストラクタは{}　()でもできるが{}のほうが良い

	if (Pad::IsPress(PAD_INPUT_UP))
	{
		move.y--;
		m_dir = kDirUp;
		isMove = true;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		move.y++;
		m_dir = kDirDown;
		isMove = true;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		move.x--;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		move.x++;
		m_dir = kDirRight;
		isMove = true;
	}

	// 正規化
	move.Normalize();
	// 長さの変更
	move *= kSpeed;
	// 座標にベクトルを足す
	m_pos += move;

	// 縦軸の移動制限
	if (m_pos.y < kGraphHalfHeight)
		m_pos.y = kGraphHalfHeight;
	else if (Game::kScreenHeight - kGraphHalfHeight < m_pos.y)
		m_pos.y = Game::kScreenHeight - kGraphHalfHeight;
	// 横軸の移動制限
	if (m_pos.x < kGraphHalfWidth)
		m_pos.x = kGraphHalfWidth;
	else if (Game::kScreenWidth - kGraphHalfWidth < m_pos.x)
		m_pos.x = Game::kScreenWidth - kGraphHalfWidth;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
	
	// 攻撃関係
	m_magicWandFrame++;
	// 魔法の杖生成
	if (kMagicWandFrame <= m_magicWandFrame)
	{
		m_magicWandFrame = 0;
		ShotMagicWand* pShot = new ShotMagicWand;
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(m_pos);
		m_pMain->AddShot(pShot);
	}
	// 聖書の生成(テスト)
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		ShotBible* pShot = new ShotBible;
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(m_pos);
		m_pMain->AddShot(pShot);
	}

	if (isMove)
	{
		// 歩きアニメーション
		m_walkAnimFrame++;
		if (kAnimFrameCycle <= m_walkAnimFrame)	m_walkAnimFrame = 0;
	}
	else
	{
		if (kUseFrame[m_walkAnimFrame/kAnimFrameNum] != 1)
		{
			m_walkAnimFrame++;
		}
		else
		{
			m_walkAnimFrame = kAnimFrameNum;
		}
	}
}

void Player::Draw() const
{
	// ダメージ演出 2フレーム間隔で表示非表示切り替え
	// 0: 表示される
	// 1: 表示される
	// 2: 非表示
	// 3: 非表示
	// 4: 表示される	…
	// % 4することで01230123012301230123…に変換する
	if (m_damageFrame % 4 >= 2) return;

	int animEle = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kGraphWidth * kUseFrame[animEle];
	int srcY = kGraphHeight * m_dir;
	
	// DXライブラリにはリファレンスページに書かれていない関数が多数存在する
	// Dxlib.hを確認してそれっぽい関数を探したり検索してみよう
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	m_colRect.Draw(0x0000ff, false);
#endif
}

void Player::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (0 < m_damageFrame) return;
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}
