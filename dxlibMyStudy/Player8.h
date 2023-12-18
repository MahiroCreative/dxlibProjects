#pragma once

#include "DxLib.h"
#include "Game8.h"
#include "Shot8.h"

// プレイヤー.
struct Player
{
private:
	int Graph;
	int X;
	int Y;
	int W;
	int H;

	// ショットのインターバルを設定するカウンター
	int shotIntervalCount;

public:
	// 初期化.
	void Init();
	// アップデート.
	void Update(Shot shot[], int shotNum);
	// 描画.
	void Draw();
};
