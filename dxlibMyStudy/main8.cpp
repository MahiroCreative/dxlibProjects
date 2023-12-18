#include "DxLib.h"
#include "Game8.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	// 背景のスクロールをするためにテクスチャモードをラッピングに修正.
	SetTextureAddressMode(DX_TEXADDRESS_WRAP);//(隠し関数.タイル並べが出来るように)
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*ゲームオブジェクトの作成*/
	Player player;
	Enemy enemy;
	Shot shot[SHOT];


	// 各初期化を呼ぶ.
	player.Init();
	enemy.Init();
	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Init();
	}

	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		// 各アップデート関数を呼ぶ.
		player.Update(shot, SHOT);
		enemy.Update();
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Update(enemy);
		}

		// 各描画関数を呼ぶ.
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Draw();
		}
		player.Draw();
		enemy.Draw();

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