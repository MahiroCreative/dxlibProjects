#include "DxLib.h"
#include "Shot.h"
#include "Player.h"

// プレイヤーの初期化処理
void InitializePlayer(Player& player)
{
	// プレイヤーのグラフィックをメモリにロード
	player.handle = LoadGraph("Resources/player.png");
	//初期位置
	player.pos.x = 288;
	player.pos.y = 400;
	// プレイヤーのグラフサイズを得る
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されいない)を代入
	player.isPrevshot = false;
}

// プレイヤーの更新
void UpdatePlayer(Player& player, Shot shot[], int shotNum)
{
	// 矢印キーを押していたらプレイヤーを移動させる
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		player.pos.y -= 3;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.pos.y += 3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.pos.x -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.pos.x += 3;
	}

	// 弾の発射処理
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
		if (player.isPrevshot == false)
		{
			// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
			for (int i = 0; i < shotNum; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (shot[i].isExist == false)
				{
					// 弾iの位置をセット、位置はプレイヤーの中心にする
					shot[i].pos.x = (player.size.w - shot[i].size.w) / 2 + player.pos.x;
					shot[i].pos.y = (player.size.h - shot[i].size.h) / 2 + player.pos.y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
					shot[i].isExist = true;

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
	if (player.pos.x < 0)
	{
		player.pos.x = 0;
	}
	if (player.pos.x > ScreenSizeX - player.size.w)
	{
		player.pos.x = ScreenSizeX - player.size.w;
	}
	if (player.pos.y < 0)
	{
		player.pos.y = 0;
	}
	if (player.pos.y > ScreenSizeY - player.size.h)
	{
		player.pos.y = ScreenSizeY - player.size.h;
	}
}

// プレイヤーの描画処理
void DrawPlayer(Player& player)
{
	// プレイヤーを描画
	DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);
}