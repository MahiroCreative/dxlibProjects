#pragma once
#include "Game.h"

struct Enemy
{
	//画像
	int handle = -1;
	int damageHandle = -1;
	//パラメータ
	Position pos;
	Size size;
	//フラグ
	bool isDamage = false;
	int damageCount = 0;
	bool isRightMove = true;
};

void InitializeEnemy(Enemy& enemy);// エネミーの初期化処理
void UpdateEnemy(Enemy& enemy);// エネミーの更新処理
void DrawEnemy(Enemy& enemy);// エネミーの描画処理