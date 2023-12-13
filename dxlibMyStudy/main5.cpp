#include "DxLib.h"

/*定数(kは定数Konstantを意味する)*/
namespace
{
	constexpr int SHOT = 20;
	constexpr int ScreenSizeX = 1280;
	constexpr int ScreenSizeY = 720;
}

/*構造体宣言*/
struct Position
{
	int x = 0;
	int y = 0;
};
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

/*グローバル変数*/
Player player;
Enemy enemy;
Shot shot[SHOT];

// プレイヤーの初期化処理
void InitializePlayer()
{
	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	player.handle = LoadGraph("Resources/player.png");
	// プレイヤーのグラフサイズを得る
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	//Pos
	player.pos.x = 288;
	player.pos.y = 400;
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されいない)を代入
	player.isPrevshot = false;
}

// エネミーの初期化処理
void InitializeEnemy()
{
	// エネミーのグラフィックをメモリにロード＆表示座標を初期化
	enemy.handle = LoadGraph("Resources/enemy.png");
	// エネミーのグラフィックをメモリにロード＆ダメージ時の状態管理用の変数を初期化
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");
	// エネミーのグラフィックのサイズを得る	
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);
	//Pos
	enemy.pos.x = 0;
	enemy.pos.y = 50;
	// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
	enemy.isDamage = false;
	enemy.damageCount = 0;
	// エネミーが右移動しているかどうかのフラグをリセット
	enemy.isRightMove = true;
}

// ショットの初期化処理
void InitializeShot()
{
	int shotHandle = LoadGraph("Resources/shot.png");
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);
	for (int i = 0; i < SHOT; i++)
	{
		// ショットのグラフィックをメモリにロード.
		shot[i].handle = shotHandle;
		// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
		shot[i].isExist = false;
		// 弾のグラフィックのサイズをえる
		shot[i].size.w = sizeW;
		shot[i].size.h = sizeH;
	}
}

// プレイヤーの更新
void UpdatePlayer()
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
			for (int i = 0; i < SHOT; i++)
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

// エネミーの更新処理
void UpdateEnemy()
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

// 弾の更新処理
void UpdateShot()
{
	for (int i = 0; i < SHOT; i++)
	{
		// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
		if (shot[i].isExist == true)
		{
			// 弾iを8ドット上に移動させる
			shot[i].pos.y -= 8;

			// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
			if (shot[i].pos.y < 0 - shot[i].size.h)
			{
				shot[i].isExist = false;
			}
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
}

// プレイヤーの描画処理
void DrawPlayer()
{
	// プレイヤーを描画
	DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);
}

// エネミーの描画処理
void DrawEnemy()
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

// 弾の描画処理
void DrawShot()
{
	for (int i = 0; i < SHOT; i++)
	{
		if (shot[i].isExist)
		{
			// 画面に弾iを描画する
			DrawGraph(shot[i].pos.x, shot[i].pos.y, shot[i].handle, FALSE);
		}
	}
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*初期化処理*/
	// プレイヤー
	InitializePlayer();
	// エネミー
	InitializeEnemy();
	// ショット
	InitializeShot();

	/*ゲームループ.*/
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//Update
		UpdatePlayer();
		UpdateEnemy();
		UpdateShot();

		// 裏画面の内容を表画面にコピーする（描画の確定）.
		DrawShot();
		DrawPlayer();
		DrawEnemy();
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

	/*終了処理*/
	DxLib::DxLib_End();//Dxlib終了処理
	return 0;//終了
}