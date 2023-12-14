#pragma once
#include "Game.h"

struct Shot;

// 構造体宣言
struct Player
{
	int handle = -1;
	Position pos;
	Size size;

	bool isPrevshot = false;
};

// プロトタイプ宣言
void InitializePlayer(Player& player);// プレイヤーの初期化処理
void UpdatePlayer(Player& player, Shot shot[], int shotNum);// プレイヤーの更新
void DrawPlayer(Player& player);