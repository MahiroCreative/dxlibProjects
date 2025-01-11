//STL.
#include <iostream>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "Player.h"


//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*定数*/
	//画面サイズ
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ

	/*変数*/
	LONGLONG roopStartTime = 0;
	LONGLONG frameTime = 0;
	bool gameRoop = true;

	/*オブジェクト生成*/
		// 描画する文字列
	const char* text = "回転する文字列";

	// 文字列の幅と高さを取得
	int textWidth = GetDrawStringWidth(text, strlen(text));
	int textHeight = GetFontSize();

	// 回転の中心座標（文字列の中心）
	double rotCenterX = textWidth / 2.0;
	double rotCenterY = textHeight / 2.0;

	

	// 回転角度
	double angle = 0.0;

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	// 画面の中心座標を取得
	int screenWidth, screenHeight;
	GetScreenState(&screenWidth, &screenHeight, NULL);
	int posX = screenWidth / 2;
	int posY = screenHeight / 2;

	/*GameRoop*/
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*ゲーム部*/
		// 回転角度を更新
		angle += DX_PI_F * 0.01;  // 毎フレーム回転角度を増加

		// 文字列を回転させて描画
		DrawRotaString(
			posX, posY,                      // 描画位置（画面の中心）
			1.0, 1.0,                        // 拡大率（等倍）
			rotCenterX, rotCenterY,          // 回転の中心座標（文字列の中心）
			angle,                           // 回転角度（ラジアン）
			GetColor(255, 255, 255),         // 文字色（白色）
			0,                               // 縁取り色（不要なので0）
			FALSE,                           // 縦書きフラグ（横書きなのでFALSE）
			text                             // 描画する文字列
		);


		//裏画面を表へ
		ScreenFlip();

		//リフレッシュ処理(-1ならエラー)
		if (ProcessMessage() < 0) { break; }

		//ループ終了処理
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		//現在の1frameにかかる時間を計測
		frameTime = GetNowHiPerformanceCount() - roopStartTime;

		//fps固定(60fps:16.66ms)
		//ループ開始時刻から16.66ms経つまで停止
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*終了処理*/
	DxLib_End();//Dxlib終了処理
	return 0;//プログラム終了 
}