#include "DxLib.h"
#include "structPlayer.h"
#include "structEnemy.h"

// プレイヤーの初期化
void initPlayer(Player* pPlayer, int tempNoHitHandle, int tempHitHandle)
{
	pPlayer->noHitHandle = tempNoHitHandle;
	pPlayer->hitHandle = tempHitHandle;
	pPlayer->x = 320.0f;
	pPlayer->y = 240.0f;
	// それぞれの当たり判定の場所を代入
	pPlayer->detectionLeft = 0;
	pPlayer->detectionRight = 32;
	pPlayer->detectionUp = 0;
	pPlayer->detectionDown = 32;
}

// プレイヤーを描画する関数
void drawPlayer(Player player, int detection)
{
	// 敵にあたったかどうか
	if (detection == NOT_HIT)
	{
		// 当たっていなければ普通ver.を描画
		DrawGraph((int)player.x, (int)player.y, player.noHitHandle, 0);
	}
	else if (detection == HIT)
	{
		// 当たっていれば×目ver.を描画
		DrawGraph((int)player.x, (int)player.y, player.hitHandle, 0);
	}
}

// 当たり判定
int CollisionDetection(Player player, Enemy enemy[])
{
	// 全キャラクターを判定 (CHARA_MAXでもOK)
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		/// 当たり判定座標 + 現在地
		// 自分
		const int playerLeftX = player.detectionLeft + player.x;
		const int playerUpY = player.detectionUp + player.y;
		const int playerRightX = player.detectionRight + player.x;
		const int playerDownY = player.detectionDown + player.y;
		// 敵
		const int enemyLeftX = enemy[i].detectionLeft + enemy[i].x;
		const int enemyUpY = enemy[i].detectionUp + enemy[i].y;
		const int enemyRightX = enemy[i].detectionRight + enemy[i].x;
		const int enemyDownY = enemy[i].detectionDown + enemy[i].y;

		/// 判定
		// 左二つの&&で左右で当たっていないか判定
		// 右二つの&&で上下で当たっていないか判定
		if ((playerLeftX < enemyRightX) && (enemyLeftX < playerRightX) && (playerUpY < enemyDownY) && (enemyUpY < playerDownY))
		{
			return HIT;
		}
	}
	return NOT_HIT;
}

// プレイヤーの移動関数
void updatePlayer(Player* pPlayer)
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((padState & PAD_INPUT_UP) != 0)		// 上キー押されている
	{
		pPlayer->y -= 2.5f;
		if (pPlayer->y < 0)	// 画面外に出ようとした
		{
			pPlayer->y = 0;
		}
	}
	if ((padState & PAD_INPUT_DOWN) != 0)	// 下キー押されている
	{
		pPlayer->y += 2.5f;
		if (pPlayer->y > 480 - 32)
		{
			pPlayer->y = 480 - 32;
		}
	}
	if ((padState & PAD_INPUT_LEFT) != 0)	// 左キー押されている
	{
		pPlayer->x -= 2.5f;
		if (pPlayer->x < 0)
		{
			pPlayer->x = 0;
		}
	}
	if ((padState & PAD_INPUT_RIGHT) != 0)	// 右キー押されている
	{
		pPlayer->x += 2.5f;
		if (pPlayer->x > 640 - 32)
		{
			pPlayer->x = 640 - 32;
		}
	}
}