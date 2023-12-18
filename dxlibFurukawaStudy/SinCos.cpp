#include <DxLib.h>
#include <cmath>
#include "Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	constexpr float kBarLen = 100;
	constexpr float kCenterX = 320;
	constexpr float kCenterY = 240;
	constexpr float kDegToRad = DX_PI_F / 180.0f;

	int angle = 0;

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		DrawCircle(kCenterX, kCenterY, 2, 0xffffff, true);
		DrawCircle(kCenterX, kCenterY, kBarLen, 0xffffff, false);

		angle++;
		float radian = angle * kDegToRad;

		float offsetX = kBarLen * cosf(radian);
		float offsetY = kBarLen * sinf(radian);
		DrawLine(kCenterX, kCenterY,
			kCenterX + offsetX, kCenterY - offsetY,
			0xff0000);

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

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}