#include "DxLib.h"

/*由比：class1*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*座標設定*/
	// x座標.
	int x = 0;
	//y座標
	int y[10];
	for (int i = 0; i < 10; i++)
	{
		y[i] = i * 48;//48ズラす
	}

	/*ゲームループ*/
	while (ProcessMessage() > -1)
	{
		/*画面初期化*/
		ClearDrawScreen();

		/*ゲーム処理*/
		// 矢印キーの→を押したら右に動かす.
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x++;
		}

		/*描画の更新*/
		for (int i = 0; i < 10; i++)
		{
			LoadGraphScreen(x, y[i], "Resources/player.png", FALSE);
		}
		ScreenFlip();//裏で作成した画面を表に

		/*ループ終了処理*/
		if (ProcessMessage() < 0)//エラー処理
		{
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))//Escでも終了する
		{
			break;
		}
	}

	/*終了処理*/
	DxLib::DxLib_End();//Dxlib終了処理
	return 0;//終了 
}
