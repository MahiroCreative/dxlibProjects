#include <DxLib.h>
#include "Shot7.h"
#include "Enemy7.h"
#include "Game.h"

void InitShot(Shot& shot, int handle, int sizeW, int sizeH)
{
	shot.handle = handle;
	shot.isShot = false;
	shot.w = sizeW;
	shot.h = sizeH;
}

void UpdateShot(Shot& shot, Enemy& enemy)
{
	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (shot.isShot == true)
	{
		// 弾iを１６ドット上に移動させる
		shot.y -= 16;

		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (shot.y < -80)
		{
			shot.isShot = false;
		}
	}

	// 弾のあたり判定.
	// 弾iが存在している場合のみ次の処理に映る
	if (shot.isShot)
	{
		// エネミーとの当たり判定
		if (((shot.x > enemy.x && shot.x < enemy.x + enemy.w) ||
			(enemy.x > shot.x && enemy.x < shot.x + shot.w)) &&
			((shot.y > enemy.y && shot.y < enemy.y + enemy.h) ||
				(enemy.y > shot.y && enemy.y < shot.y + shot.h)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.isShot = false;

			// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
			enemy.isDamage = true;

			// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
			enemy.damageCounter = 0;
		}
	}
}

void DrawShot(Shot& shot)
{
	if (!shot.isShot) return;

	// 画面に弾iを描画する
	DrawGraph(shot.x, shot.y, shot.handle, FALSE);
}
