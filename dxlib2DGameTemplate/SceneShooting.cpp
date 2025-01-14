#include "SceneShooting.h"

/*メンバ関数*/

void SceneShooting::Init()
{
	//変数初期化
	_nextScene = GameSetting::SceneState::ShootingGame;

	//ゲームオブジェクト生成
	_player = std::make_unique<ShootingPlayer>();

	//初期化
	_player->Init(Vector2{100,GameSetting::WINDOW_CENTER_Y});
}

int SceneShooting::Update()
{
	//Key入力の更新
	InputKey::Update();

	//Bでタイトルに戻る
	CheckReturnTitle(KEY_INPUT_B);

	//player更新
	_player->Update();


	//int型に変換して返す
	return static_cast<int>(_nextScene);
}

void SceneShooting::Draw()
{
	//現在のシーン名を表示
	DrawString(0, 0, "ShootingGame: WASD(上左下右),Enter(Shot),B(タイトル)", GetColor(255, 255, 255));
	//player描画
	_player->Draw();
}

void SceneShooting::CheckReturnTitle(int KeyCode)
{
	if (InputKey::isDownKey(KeyCode))
	{
		_nextScene = GameSetting::SceneState::Title;
	}

}
