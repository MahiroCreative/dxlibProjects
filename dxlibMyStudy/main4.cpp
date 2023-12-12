#include "DxLib.h"

/*定数(kは定数Konstantを意味する)*/
namespace
{
	constexpr int kShotNum = 20;//最大弾数
}

/*構造体宣言*/
//オブジェクトの位置
struct Position
{
	int x = 0;
	int y = 0;
};
//オブジェクトの大きさ
struct Size
{
	int w = 0;
	int h = 0;
};

struct Player
{
	int handle = -1;
	Position pos;
	Size size;

	bool isPrevshot = false;
};

struct Enemy
{
	int handle = -1;
	int damageHandle = -1;
	Position pos;
	Size size;

	bool isDamage = false;
	int damageCount = 0;

	bool isRightMove = true;
};

struct Shot
{
	int handle = -1;
	Position pos;
	Size size;

	bool isExist = false;
};

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(640, 480, 16);		// 解像度を640*480、colorを16bitに設定.
	ChangeWindowMode(TRUE);			// ウインドウモードに.

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	Player player;
	player.handle = LoadGraph("data/texture/player.png");
	player.pos.x = 288;
	player.pos.y = 400;

	// プレイヤーのグラフサイズを得る
	GetGraphSize(player.handle, &player.size.w, &player.size.h);

	// エネミーのグラフィックをメモリにロード＆表示座標を初期化
	Enemy enemy;
	enemy.handle = LoadGraph("data/texture/enemy.png");
	enemy.pos.x = 0;
	enemy.pos.y = 50;

	// エネミーのグラフィックをメモリにロード＆ダメージ時の状態管理用の変数を初期化
	enemy.damageHandle = LoadGraph("data/texture/enemyDamage.png");

	// エネミーのグラフィックのサイズを得る	
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);

	// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
	enemy.isDamage = false;
	enemy.damageCount = 0;

	Shot shot[kShotNum];
	int shotHandle = LoadGraph("data/texture/shot.png");
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);
	for (int i = 0; i < kShotNum; i++)
	{
		// ショットのグラフィックをメモリにロード.
		shot[i].handle = shotHandle;
		// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
		shot[i].isExist = false;
		// 弾のグラフィックのサイズをえる
		shot[i].size.w = sizeW;
		shot[i].size.h = sizeH;
	}

	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されいない)を代入
	player.isPrevshot = false;

	// エネミーが右移動しているかどうかのフラグをリセット
	enemy.isRightMove = true;

	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//------------------------------//
		// プレイヤールーチン
		//------------------------------//
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
					for (int i = 0; i < kShotNum; i++)
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
			if (player.pos.x > 640 - player.size.w)
			{
				player.pos.x = 640 - player.size.w;
			}
			if (player.pos.y < 0)
			{
				player.pos.y = 0;
			}
			if (player.pos.y > 480 - player.size.h)
			{
				player.pos.y = 480 - player.size.h;
			}

			// プレイヤーを描画
			DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);
		}

		//------------------------------//
		// エネミールーチン
		//------------------------------//
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
			if (enemy.pos.x > 640 - enemy.size.w)
			{
				enemy.pos.x = 640 - enemy.size.w;
				enemy.isRightMove = false;
			}
			else if (enemy.pos.x < 0)
			{
				enemy.pos.x = 0;
				enemy.isRightMove = true;
			}

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

		//------------------------------//
		// 弾ルーチン
		//------------------------------//
		for (int i = 0; i < kShotNum; i++)
		{
			// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
			if (shot[i].isExist == true)
			{
				// 弾iを１６ドット上に移動させる
				shot[i].pos.y -= 16;

				// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
				if (shot[i].pos.y < 0 - shot[i].size.h)
				{
					shot[i].isExist = false;
				}

				// 画面に弾iを描画する
				DrawGraph(shot[i].pos.x, shot[i].pos.y, shot[i].handle, FALSE);
			}

			// 弾のあたり判定.
			// 弾iが存在している場合のみ次の処理に映る
			if (shot[i].isExist == 1)
			{
				// エネミーとの当たり判定
				if (((shot[i].pos.x > enemy.pos.x && shot[i].pos.x < enemy.pos.x + enemy.size.w) ||
					(enemy.pos.x > shot[i].pos.x && enemy.pos.x < shot[i].pos.x + shot[i].size.w)) &&
					((shot[i].pos.y > enemy.pos.y && shot[i].pos.y < enemy.pos.y + enemy.size.h) ||
						(enemy.pos.y > shot[i].pos.y && enemy.pos.y < shot[i].pos.y + shot[i].size.h)))
				{
					// 接触している場合は当たった弾の存在を消す
					shot[i].isExist = 0;

					// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
					enemy.isDamage = true;

					// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
					enemy.damageCount = 0;
				}
			}
		}

		// 裏画面の内容を表画面にコピーする（描画の確定）.
		ScreenFlip();


		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}