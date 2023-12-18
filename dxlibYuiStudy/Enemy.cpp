#include "DxLib.h"
#include "Enemy.h"

// エネミーの初期化処理
void InitializeEnemy(Enemy& enemy)
{
	// エネミーのグラフィックをメモリにロード＆表示座標を初期化
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.pos.x = 0;
	enemy.pos.y = 50;

	// エネミーのグラフィックをメモリにロード＆ダメージ時の状態管理用の変数を初期化
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");

	// エネミーのグラフィックのサイズを得る	
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);

	// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
	enemy.isDamage = false;
	enemy.damageCount = 0;

	// エネミーが右移動しているかどうかのフラグをリセット
	enemy.isRightMove = true;
}

// エネミーの更新処理
void UpdateEnemy(Enemy& enemy)
{
	// エネミーの座標を移動している方向に移動する
	if (enemy.isRightMove == true)
	{
		enemy.pos.x += 3;
	}
	else
	{
		enemy.pos.x -= 3;
	}

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (enemy.pos.x > ScreenSizeX - enemy.size.w)
	{
		enemy.pos.x = ScreenSizeX - enemy.size.w;
		enemy.isRightMove = false;
	}
	else if (enemy.pos.x < 0)
	{
		enemy.pos.x = 0;
		enemy.isRightMove = true;
	}
}

// エネミーの描画処理
void DrawEnemy(Enemy& enemy)
{
	// エネミーを描画
	// 顔を歪めているかどうかで処理を分岐
	if (enemy.isDamage == true)
	{
		// 顔を歪めている場合はダメージ時のグラフィックを描画する
		DrawGraph(enemy.pos.x, enemy.pos.y, enemy.damageHandle, FALSE);

		// 顔を歪めている時間を測るカウンターに１を加算する
		enemy.damageCount++;

		// もし顔を歪め初めて ３０ フレーム経過していたら顔の歪んだ状態から
		// 元に戻してあげる
		if (enemy.damageCount == 30)
		{
			// 『歪んでいない』を表す０を代入
			enemy.isDamage = 0;
		}
	}
	else
	{
		DrawGraph(enemy.pos.x, enemy.pos.y, enemy.handle, FALSE);
	}
}