#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"

class TitleScene
{
private:
	SceneKind _nextScene;
public:
	TitleScene() :
		_nextScene(SceneKind::TITLESCENE)
	{
	};
	/*ÉÅÉìÉoä÷êî*/
	SceneKind Update()
	{
		//debug.
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMESCENE1;
		}

		return _nextScene;
	}
	void Draw()
	{
		DrawString(600, 480, "title", GetColor(255, 255, 255));
	}
};