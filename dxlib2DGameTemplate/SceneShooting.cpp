#include "SceneShooting.h"

/*メンバ関数*/

void SceneShooting::Init()
{
}

int SceneShooting::Update()
{
	return static_cast<int>(GameSetting::SceneState::ShootingGame);
}

void SceneShooting::Draw()
{
	DrawString(0, 0, "ShootingGame", GetColor(255, 255, 255));
}
