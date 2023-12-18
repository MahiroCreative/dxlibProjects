#pragma once

#include "DxLib.h"
#include "Game8.h"
#include "Enemy8.h"

// ショット.
struct Shot
{
private:
	int		Graph;
	int		X;
	int		Y;
	bool	isVisible;
	int		W;
	int		H;

public:
	// 初期化.
	void Init();
	// アップデート.
	void Update(Enemy& enemy);
	// 描画.
	void Draw();

	// getter
	bool IsVisible() const { return isVisible; }
	int GetSizeW() const { return W; }
	int GetSizeH() const { return H; }

	void OnShoot(int startX, int startY);
};
