#include "OverScene.h"

void OverScene::Init()
{
	//変数初期化
	_nextScene = static_cast<int>(GameSetting::SceneState::Title);
}
