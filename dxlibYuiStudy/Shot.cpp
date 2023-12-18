#include "DxLib.h"
#include "Enemy.h"
#include "Shot.h"

// ショットの初期化処理
void InitializeShot(Shot& shot, int handle, int sizeW, int sizeH)
{
	// ショットのグラフィックをメモリにロード.
	shot.handle = handle;
	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
	shot.isExist = false;
	// 弾のグラフィックのサイズをえる
	shot.size.w = sizeW;
	shot.size.h = sizeH;
}

// 弾の更新処理
void UpdateShot(Shot& shot, Enemy& enemy)
{
	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (shot.isExist == true)
	{
		// 弾iを１６ドット上に移動させる
		shot.pos.y -= ShotSpped;

		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (shot.pos.y < 0 - shot.size.h)
		{
			shot.isExist = false;
		}
	}

	// 弾のあたり判定.
	// 弾iが存在している場合のみ次の処理に映る
	if (shot.isExist == 1)
	{
		// エネミーとの当たり判定
		if (((shot.pos.x > enemy.pos.x && shot.pos.x < enemy.pos.x + enemy.size.w) ||
			(enemy.pos.x > shot.pos.x && enemy.pos.x < shot.pos.x + shot.size.w)) &&
			((shot.pos.y > enemy.pos.y && shot.pos.y < enemy.pos.y + enemy.size.h) ||
				(enemy.pos.y > shot.pos.y && enemy.pos.y < shot.pos.y + shot.size.h)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.isExist = 0;

			// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
			enemy.isDamage = true;

			// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
			enemy.damageCount = 0;
		}
	}
}

// 弾の描画処理
void DrawShot(Shot& shot)
{
	if (shot.isExist)
	{
		// 画面に弾iを描画する
		DrawGraph(shot.pos.x, shot.pos.y, shot.handle, FALSE);
	}
}
