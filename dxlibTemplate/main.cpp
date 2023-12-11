#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化処理*/
	//ウィンドウモードに設定
	ChangeWindowMode(TRUE); 
	//画面サイズ変更
	SetGraphMode(1280, 720, 32);
	//ＤＸライブラリ初期化(エラー時に終了)
	if (DxLib_Init() == -1){return -1;}

	/*ゲーム処理*/
	// 点を打つ
	DrawPixel(320, 240, GetColor(255, 255, 255));
	// キー入力待ち
	WaitKey();				
	// ＤＸライブラリ使用の終了処理
	DxLib_End();				

	return 0;
}