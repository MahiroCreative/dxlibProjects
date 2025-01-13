#include "ScenePlatform.h"

/*メンバ関数*/

void ScenePlatform::Init()
{
}

int ScenePlatform::Update()
{
	return static_cast<int>(GameSetting::SceneState::PlatformGame);
}

void ScenePlatform::Draw()
{
	DrawString(0, 0, "PlatformGame", GetColor(255, 255, 255));
}
