#include "DxLib.h"
#include "Player7.h"
#include "Shot7.h"
#include "Enemy7.h"
#include "Game7.h"

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*ゲームオブジェクトの作成*/
	Player player;
	Enemy enemy;
	Shot shot[ShotNum];

	/*オブジェクト初期化*/
	InitPlayer(player);
	InitEnemy(enemy);
	int shotGraph, sizeW, sizeH;
	shotGraph = LoadGraph("Resources/shot.png");//弾の画像
	GetGraphSize(shotGraph, &sizeW, &sizeH);//弾サイズ
	for (int i = 0; i < ShotNum; i++)//全ての弾を初期化
	{
		InitShot(shot[i], shotGraph, sizeW, sizeH);
	}


	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//------------------------------//
		// プレイヤールーチン
		//------------------------------//
		UpdatePlayer(player, shot, ShotNum);
		DrawPlayer(player);

		//------------------------------//
		// エネミールーチン
		//------------------------------//
		UpdateEnemy(enemy);
		DrawEnemy(enemy);

		//------------------------------//
		// 弾ルーチン
		//------------------------------//
		for (int i = 0; i < ShotNum; i++)
		{
			UpdateShot(shot[i], enemy);
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