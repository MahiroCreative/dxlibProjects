#include <DxLib.h>
#include "Player7.h"
#include "Shot7.h"
#include "Game.h"

void InitPlayer(Player& player)
{
	player.handle = LoadGraph("Resources/player.png");
	player.x = 288;
	player.y = 400;
	GetGraphSize(player.handle, &player.w, &player.h);

	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されいない)を代入
	player.isPrevshot = false;
}

void UpdatePlayer(Player& player, Shot shot[], int shotArrayNum)
{
	// 矢印キーを押していたらプレイヤーを移動させる
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		player.y -= 3;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.y += 3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.x -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.x += 3;
	}

	// 弾の発射処理
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
		if (player.isPrevshot == false)
		{
			// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
			for (int i = 0; i < shotArrayNum; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (shot[i].isShot == false)
				{
					// 弾iの位置をセット、位置はプレイヤーの中心にする
					shot[i].x = (player.w - shot[i].w) / 2 + player.x;
					shot[i].y = (player.h - shot[i].h) / 2 + player.y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
					shot[i].isShot = true;

					// 一つ弾を出したので弾を出すループから抜けます
					break;
				}
			}
		}

		// 前フレームでショットボタンを押されていたかを保存する変数にtrue(おされていた)を代入
		player.isPrevshot = true;
	}
	else
	{
		// ショットボタンが押されていなかった場合は
		// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
		player.isPrevshot = false;
	}

	// プレイヤーが画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
	if (player.x < 0)
	{
		player.x = 0;
	}
	if (player.x > ScreenSizeX - 64)
	{
		player.x = ScreenSizeX - 64;
	}
	if (player.y < 0)
	{
		player.y = 0;
	}
	if (player.y > ScreenSizeY - 64)
	{
		player.y = ScreenSizeY - 64;
	}
}

void DrawPlayer(Player& player)
{
	// プレイヤーを描画
	DrawGraph(player.x, player.y, player.handle, FALSE);
}
