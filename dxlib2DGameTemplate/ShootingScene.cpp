#include "ShootingScene.h"

/*メンバ関数*/

void ShootingScene::Init()
{
	//変数初期化
	_nextScene = GameSetting::SceneState::ShootingGame;
	_playerBulletTimer = 0;
	_playerChargeFrame = 0;

	//ゲームオブジェクト生成
	_player = std::make_unique<ShootingPlayer>();
	_enemy = std::make_unique<ShootingEnemy>();

	//初期化
	_player->Init(Vector2{100,GameSetting::WINDOW_CENTER_Y});
	_enemy->Init(Vector2{ GameSetting::WINDOW_WIDTH - 80 ,GameSetting::WINDOW_CENTER_Y});
}

int ShootingScene::Update()
{
	//Key入力の更新
	InputKey::Update();

	//Bでタイトルに戻る
	CheckReturnTitle(KEY_INPUT_B);

	//player更新
	_player->Update();
	//enemy更新
	_enemy->Update();

	//PlayerBulletの生成
	CreatePlayerBullet();
	//ChageBulletの生成
	CreateChargeBullet();
	//PlayerBullet更新
	UpdatePlayerBullet();
	//PlayerBulletの削除
	DeletePlayerBullet();

	//int型に変換して次のシーンを返す
	return static_cast<int>(_nextScene);
}

void ShootingScene::Draw()
{
	//現在のシーン名を表示
	DrawString(0, 0, "ShootingGame: WASD(上左下右),Enter(Shot),B(タイトル)", GetColor(255, 255, 255));
	//PlayerBullet描画
	DrawPlayerBullet();
	//player描画
	_player->Draw();
	//enemy描画
	_enemy->Draw();

}

void ShootingScene::CheckReturnTitle(int KeyCode)
{
	if (InputKey::isDownKey(KeyCode))
	{
		_nextScene = GameSetting::SceneState::Title;
	}
}

void ShootingScene::DrawPlayerBullet()
{
	for (auto& bullet : _vPlayerBullets)
	{
		bullet->Draw();
	}
}

void ShootingScene::CreatePlayerBullet()
{
	//PlayerBulletの生成
	if (InputKey::isDownKey(KEY_INPUT_RETURN) && _playerBulletTimer >= 10)
	{
		//Bulletの生成
		_pPlayerBullet = std::make_unique<SimpleBullet>();
		//初期化
		_pPlayerBullet->Init(_player->GetTransform().Position, 8.0f);
		//Bulletの追加
		_vPlayerBullets.push_back(std::move(_pPlayerBullet));
		//Bulletの発射間隔のリセット
		_playerBulletTimer = 0;
	}
	//Bulletの発射timerの更新
	_playerBulletTimer++;
}

void ShootingScene::UpdatePlayerBullet()
{
	//PlayerBulletの更新
	for (auto& bullet : _vPlayerBullets)
	{
		bullet->Update();
	}
}

void ShootingScene::DeletePlayerBullet()
{
	// 全弾チェック
	for (auto it = _vPlayerBullets.begin(); it != _vPlayerBullets.end();)
	{
		if ((*it)->IsOutOfScreen())
		{
			// 画面外に出た弾を削除
			//(削除した場合、空いた場所に後ろの要素が詰められる)
			it = _vPlayerBullets.erase(it);
		}
		else
		{
			// 次の要素へ
			++it;
		}
	}
}

void ShootingScene::CreateChargeBullet()
{
	//ChargeBulletの生成条件
	bool isCharge = (_playerChargeFrame >= 80);//30Frame以上押されているか
	bool isRelease = !(InputKey::isHoldKey(KEY_INPUT_RETURN));//リリースされたか

	//Chaege時間計測
	if (InputKey::isHoldKey(KEY_INPUT_RETURN)) { _playerChargeFrame++; }
	else { _playerChargeFrame = 0; }

	//ChargeBulletの生成
	if (isCharge && isRelease)
	{
		//ChargeBulletの生成
		_pPlayerBullet = std::make_unique<SimpleBullet>();
		_pPlayerBullet->Init(_player->GetTransform().Position, 8.0f, 20);
		//Bulletの追加
		_vPlayerBullets.push_back(std::move(_pPlayerBullet));
	}
}
