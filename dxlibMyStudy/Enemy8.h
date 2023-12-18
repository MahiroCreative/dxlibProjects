//-----------------------------------------------------------------------------
// @brief  エネミー処理.
//-----------------------------------------------------------------------------

#pragma once

#include "DxLib.h"
#include "Game8.h"

// エネミー構造体.
class Enemy
{
private:
	int		X;
	int		Y;
	int		Graph;
	bool	DamageFlag;
	int		DamageCounter;
	int		DamageGraph;
	int		W;
	int		H;
	int		Life;

	// エネミーが右移動しているかどうか
	bool	RightMove;

public:
	// 初期化.
	void Init();
	// アップデート.
	void Update();
	// 描画.
	void Draw();
	void OnDamage();

	// getter
	int GetPosX() const { return X; }
	int GetPosY() const { return Y; }
	int GetSizeW() const { return W; }
	int GetSizeH() const { return H; }
	int GetLife() const { return Life; }
};
