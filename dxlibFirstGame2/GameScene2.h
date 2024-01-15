#pragma once
#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene2
{
private:
	SceneKind _nextScene;
public:
	GameScene2() :
		_nextScene(SceneKind::GAMESCENE2)
	{
	};
	/*ÉÅÉìÉoä÷êî*/
	SceneKind Update()
	{
		//debug.
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMEEND;
		}

		return _nextScene;
	}
	void Draw()
	{
		DrawString(600, 480, "gameScene2", GetColor(255, 255, 255));
	}

};