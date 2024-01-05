#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "GameCommon.h"

class Player
{
public:
	/*コンストラクタ*/
	Player()
	{
		_pos = IntVector();
		_drawHandle = LoadGraph("Resources/player.png");
	}
	/*メンバ関数*/
	void Update()
	{
		_pos.X += 1;
		_pos.Y += 1;
	}
	void Draw()
	{
		DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
	}
	void Sound(){}
private:
	/*メンバ変数*/
	int _drawHandle;//画像ハンドル
	IntVector _pos;//座標
};

