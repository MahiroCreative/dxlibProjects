#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene1
{
private:
	SceneKind _nextScene;
public:
	GameScene1() :
		_nextScene(SceneKind::GAMESCENE1)
	{
	};
	/*ÉÅÉìÉoä÷êî*/
	SceneKind Update()
	{
		//debug.
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMESCENE2;
		}

		return _nextScene;
	}
	void Draw()
	{
		DrawString(600, 480, "gameScene1", GetColor(255, 255, 255));
	}

};