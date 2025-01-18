#pragma once
#include "DxLib.h"
#include "Vector2.h"

struct CircleCollision2D
{
	/*メンバ変数*/
	//中心座標
	Vector2 Center;
	//半径
	float Radius;
	//Debug用Drawの色
	unsigned int Color;

	/*メンバ関数*/
	//コリジョンの描画
	void Draw()
	{
		DrawCircle(static_cast<int>(Center.X), static_cast<int>(Center.Y), static_cast<int>(Radius), Color, FALSE);
	}
};