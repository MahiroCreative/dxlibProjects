#pragma once
#include "MyGameLib.h"
#include "DxLib.h"

class TitleScene
{
public:
	/*ÉÅÉìÉoä÷êî*/
	int Update()
	{
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			DrawString(600, 480, "titlefefeef", GetColor(255, 255, 255));
		}
		return 0;
	}
	void Draw()
	{
		DrawString(600, 480, "title", GetColor(255, 255, 255));
	}

};