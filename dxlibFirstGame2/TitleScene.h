#pragma once

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
		//debug.
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			ans += 1;
		}

		return 0;
	}
	void Draw()
	{
		if (ans > 1)
		{
			DrawString(600, 480, "title2", GetColor(255, 255, 255));
		}
		else
		{
			DrawString(600, 480, "title", GetColor(255, 255, 255));
		}

	}

};