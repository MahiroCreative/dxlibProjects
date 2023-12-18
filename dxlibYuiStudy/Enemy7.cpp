#include <DxLib.h>
#include "Enemy7.h"
#include "Game.h"

void InitEnemy(Enemy& enemy)
{
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.x = 0;
	enemy.y = 50;

	// エネミーのグラフィックをメモリにロード＆ダメージ時の状態管理用の変数を初期化
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");

	// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
	enemy.isDamage = false;

	// エネミーのグラフィックのサイズを得る
	GetGraphSize(enemy.handle, &enemy.w, &enemy.h);

	// エネミーが右移動しているかどうかのフラグをリセット
	enemy.isRightMove = true;
}

void UpdateEnemy(Enemy& enemy)
{
	// エネミーの座標を移動している方向に移動する
	if (enemy.isRightMove == true)
	{
		enemy.x += 3;
	}
	else
	{
		enemy.x -= 3;
	}

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (enemy.x > ScreenSizeX - 24)
	{
		enemy.x = ScreenSizeX - 24;
		enemy.isRightMove = false;
	}
	else if (enemy.x < 0)
	{
		enemy.x = 0;
		enemy.isRightMove = true;
	}

	if (enemy.isDamage)
	{

		// 顔を歪めている時間を測るカウンターに１を加算する
		enemy.damageCounter++;

		// もし顔を歪め初めて ３０ フレーム経過していたら顔の歪んだ状態から
		// 元に戻してあげる
		if (enemy.damageCounter == 30)
		{
			enemy.isDamage = false;
		}
	}
}

void DrawEnemy(Enemy& enemy)
{
	// エネミーを描画
			// 顔を歪めているかどうかで処理を分岐
	if (enemy.isDamage)
	{
		// 顔を歪めている場合はダメージ時のグラフィックを描画する
		DrawGraph(enemy.x, enemy.y, enemy.damageHandle, FALSE);
	}
	else
	{
		DrawGraph(enemy.x, enemy.y, enemy.handle, FALSE);
	}
}
