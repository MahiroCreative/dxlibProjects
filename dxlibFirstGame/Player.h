#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "GameObjectBase.h"

class Player : public GameObjectBase
{
private:
	/*メンバ変数*/
	int _drawHandle;//画像ハンドル
	IntVector _pos;//座標
public:
	/*コンストラクタ*/
	Player()
	{
		_pos = IntVector();
		_drawHandle = LoadGraph("Resources/player.png");
	}
	/*メンバ関数*/
	void Update() override
	{
		_pos.X += 1;
		_pos.Y += 1;
	}
	void Draw() const override
	{
		DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
	}
	void Sound() const override
	{

	}
};

