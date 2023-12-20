#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1;}//Dxlib初期化

	/*ゲーム部*/
	WaitKey();// キー入力待ち


	/*終了処理*/
	DxLib_End();//Dxlib終了処理
	return 0;//終了 
}