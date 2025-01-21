#include "OverScene.h"

void OverScene::Init()
{
	//変数初期化
	_nextScene = GameSetting::SceneState::OverGame;	
}

int OverScene::Update()
{
	//int型に変換して次のシーンを返す
	return static_cast<int>(_nextScene);
}

void OverScene::Draw()
{
	DrawString(0,0,"OverScene",Color::WhiteColor);
}

void OverScene::CheckReturnTitle(int KeyCode)
{
}
