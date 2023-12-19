#pragma once

#include "structEnemy.h"

#define HIT 1
#define NOT_HIT 0

typedef struct Player
{
	int noHitHandle;				// 当たっていない時の画像情報を入れる
	int hitHandle;				// 当たっている時の画像情報を入れる
	float x;				// 現在のX座標
	float y;				// 現在のY座標
	float detectionLeft;	// 当たり判定左側
	float detectionRight;	// 当たり判定右側
	float detectionUp;		// 当たり判定上側
	float detectionDown;	// 当たり判定下側
}Player;

// プレイヤーの初期化
void initPlayer(Player* pPlayer, int noHitHandle, int hitHandle);

// プレイヤーを描画する関数(第二引数に当たっているかの判定)
void drawPlayer(Player player, int detection);

// 当たり判定
int CollisionDetection(Player player, Enemy enemy[]);

// プレイヤーの移動関数
void updatePlayer(Player* pPlayer);