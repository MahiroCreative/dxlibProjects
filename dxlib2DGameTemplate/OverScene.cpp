#include "OverScene.h"

void OverScene::Init()
{
	//変数初期化
	_nextScene = GameSetting::SceneState::OverGame;	
	//初期化
	_overText.Init("OverScene", Vector2{ GameSetting::WINDOW_CENTER_X - 100,GameSetting::WINDOW_CENTER_Y });
	_overText.Transform.Scale = Vector2{ 4,4 };
}

int OverScene::Update()
{
	//int型に変換して次のシーンを返す
	return static_cast<int>(_nextScene);
}

void OverScene::Draw()
{
	DrawString(0,0,"OverScene",Color::WhiteColor);

	//シーンロゴ表示
	_overText.Draw();
}

void OverScene::CheckReturnTitle(int KeyCode)
{
}
