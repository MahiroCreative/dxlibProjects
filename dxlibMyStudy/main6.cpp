//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Shot.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	Player player;
	Enemy enemy;
	Shot shot[SHOT];

	// プレイヤーの初期化処理
	InitializePlayer(player);

	// エネミーの初期化処理
	InitializeEnemy(enemy);

	// ショットの初期化処理
	int shotHandle = LoadGraph("Resources/shot.png");
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);
	for (int i = 0; i < SHOT; i++)
	{
		InitializeShot(shot[i], shotHandle, sizeW, sizeH);
	}

	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//プレイヤーの更新処理
		UpdatePlayer(player, shot, SHOT);
		// プレイヤーの描画処理
		DrawPlayer(player);

		//エネミーの更新処理
		UpdateEnemy(enemy);
		// エネミーの描画処理
		DrawEnemy(enemy);

		//弾の更新処理
		for (int i = 0; i < SHOT; i++)
		{
			UpdateShot(shot[i], enemy);
			// 弾の描画処理
			DrawShot(shot[i]);
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