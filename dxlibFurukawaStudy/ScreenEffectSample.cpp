#include <DxLib.h>
#include "Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	//SetDrawScreenで描画対象にできるグラフィックハンドルを作成する
	int screen = MakeScreen(ScreenSizeX, ScreenSizeY, true);

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		//ClearDrawScreen();

		// ゲームの処理
		SetDrawScreen(screen);

		// screenに描画する
		// 画面をクリアしていないので前の状態に上書きされて線が引ける

		// 画面を覆う半透明(6.25%ぐらいの不透明度)の四角を描画している
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16);
		DrawBox(0, 0,ScreenSizeX , ScreenSizeY, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// マウスの現在位置と、左クリックが押されているかをチェック
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		bool isLeft = (GetMouseInput() & MOUSE_INPUT_LEFT);

		// 左クリックが押されていたら丸を描画する
		if (isLeft)
		{
			DrawCircle(mouseX, mouseY, 8, 0xffff00, true);
		}

		// デフォルトのバックバッファへの書き込みに戻す
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		DrawGraph(0, 0, screen, true);
		//DrawCircle(mouseX, mouseY, 8, 0xff0000, true);

		//// 10進、16進表記の復習
		//int x = 10;		// 10進数の10、16進数のaが入る
		//int y = 0x10;	// 0xで始まる数字は16進数
		//				// 16進数の10、10進数の16が入る
		//DrawFormatString(10,  0, 0xffffff, "%d", x);	// 10
		//DrawFormatString(10, 16, 0xffffff, "%d", y);	// 16
		//DrawFormatString(10, 32, 0xffffff, "0x%x", x);	// 0xa
		//DrawFormatString(10, 48, 0xffffff, "0x%x", y);	// 0x10


		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		// 16.66ms(16667マイクロ秒)経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	DeleteGraph(screen);
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}