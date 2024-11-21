//STL.
#include <iostream>
//origin.
#include "MyDxlib/MyDxlib.h"
//debug.
#define DEBUG


//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*コンソールDebug用*/
#ifdef DEBUG
	AllocConsole();                                        // コンソール
	FILE* out = 0; freopen_s(&out, "CON", "w", stdout); // stdout
	FILE* in = 0; freopen_s(&in, "CON", "r", stdin);   // stdin

#endif

	/*定数*/
	//画面サイズ
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ

	/*変数*/
	LONGLONG roopStartTime = 0;
	LONGLONG frameTime = 0;
	bool gameRoop = true;

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*GameRoop*/
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*シーン遷移処理*/
		

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

		//Debug表示
#ifdef DEBUG
		//現在のフレームラップを表示
		printf("frame:%d ", frameTime);
		//現在時刻を表示
		MyTool::TimeTool::ShowNowTime();
		//改行
		printf("\n");
#endif // DEBUG
	}

	/*終了処理*/
	DxLib_End();//Dxlib終了処理
#ifdef DEBUG//コンソールDebug用
	fclose(out); fclose(in); FreeConsole();//コンソール解放
#endif
	return 0;//プログラム終了 
}