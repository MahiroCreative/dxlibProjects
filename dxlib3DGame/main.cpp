#include "DxLib.h"
#include "string"
#include "GameMath.h"
#include "GameTool.h"

using namespace std;

/*概要*/
//ここでは画面サイズとゲームループのみ行う。
//ゲームそのものの処理はGameMain以下で行う。

//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*定数*/
	//画面サイズ
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ

	/*変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	DebugString dString;

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*gameRoop.*/
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*ゲーム処理*/
		Vector3 v1;
		Vector3 v2;
		Vector3 v3;
		Vector3 v4;
		Vector3 v5;
		Vector3 v6;
		v1.X = 1.2f; v1.Y = 1.2f; v1.Z = 1.2f;
		v2.X = 1.6f; v2.Y = 1.0f; v2.Z = 2.2f;
		v3 = v1 + v2;
		v4 = v1 - v2;
		v5.X = 0.1f;
		v5 += v1;
		v6.Y = 0.2f;
		v6 -= v2;

		/*Debug表示*/
		dString.value1 = to_string(v3.X);
		dString.value2 = to_string(v3.Y);
		dString.value3 = to_string(v3.Z);
		dString.value4 = to_string(v4.X);
		dString.value5 = to_string(v4.Y);
		dString.value6 = to_string(v4.Z);
		dString.value7 = to_string(v5.X);
		dString.value8 = to_string(v5.Y);
		dString.value9 = to_string(v5.Z);
		dString.value10 = to_string(v6.X);
		dString.value11 = to_string(v6.Y);
		dString.value12 = to_string(v6.Z);
		DebugDraw(&dString);


		//裏画面を表へ
		ScreenFlip();

		//リフレッシュ処理(-1ならエラー)
		if (ProcessMessage() < 0) { break; }

		//ループ終了処理
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		//fps固定(60fps:16.66ms)
		//ループ開始時刻から16.66ms経つまで停止
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*終了処理*/
	DxLib_End();//Dxlib終了処理
	return 0;//終了 
}