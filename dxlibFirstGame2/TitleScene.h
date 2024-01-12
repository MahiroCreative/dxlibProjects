#pragma once
#include "MyGameLib.h"
#include "DxLib.h"

class TitleScene
{
private:
	int ans;
public:
	TitleScene() :
		ans(0)
	{
	};
	/*ƒƒ“ƒoŠÖ”*/
	int Update()
	{
		/*Key“ü—Í‚ÌXV*/
		MyKeyInput::Update();

		//debug.
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			ans = -1;
		}

		return ans;
	}
	void Draw()
	{
		DrawString(600, 480, "title", GetColor(255, 255, 255));
	}

};