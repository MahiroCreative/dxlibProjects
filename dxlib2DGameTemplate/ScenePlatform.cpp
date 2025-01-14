#include "ScenePlatform.h"

/*メンバ関数*/

void ScenePlatform::Init()
{
	_nextScene = GameSetting::SceneState::PlatformGame;
}

int ScenePlatform::Update()
{
	//Key入力の更新
	InputKey::Update();

	//Enterキーが押されたらタイトルシーンに遷移
	if (InputKey::isDownKey(KEY_INPUT_RETURN))
	{
		_nextScene = GameSetting::SceneState::Title;
	}

	//int型に変換して返す
	return static_cast<int>(_nextScene);
}

void ScenePlatform::Draw()
{
	DrawString(0, 0, "PlatformGame", GetColor(255, 255, 255));
}
