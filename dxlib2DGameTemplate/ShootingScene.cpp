#include "ShootingScene.h"

/*メンバ関数*/

void ShootingScene::Init()
{
	//変数初期化
	_nextScene = GameSetting::SceneState::ShootingGame;

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
	_enemy->Update();

	//int型に変換して返す
	return static_cast<int>(_nextScene);
}

void ShootingScene::Draw()
{
	//現在のシーン名を表示
	DrawString(0, 0, "ShootingGame: WASD(上左下右),Enter(Shot),B(タイトル)", GetColor(255, 255, 255));
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
