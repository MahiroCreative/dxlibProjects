#include "DxLib.h"

/*由比：class1*/

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1;}//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*リソース読み込み*/
	int playerGraph = LoadGraph("Resources/player.png");//Player
	int enemyGraph = LoadGraph("Resources/enemy.png");//Enemy

	/*Playerセッティング*/
	//初期位置
	int playerX = 280;
	int playerY = 400;

	/*Enemyセッティング*/
	//初期位置
	int enemyX = 320;
	int enemyY = 240;
	//移動量
	int enemyMoveX = 3;


	/*ゲームループ*/
	while (true)
	{
		/*画面初期化(真っ暗にする)*/
		ClearDrawScreen();

		/*ゲーム処理*/
		//Player処理
		{
			//Key入力による移動
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				playerY -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				playerY += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				playerX -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				playerX += 3;
			}

			//画面外に出ないようにする
			if (playerX < 0)
			{
				playerX = 0;
			}
			if (playerX > 1280 - 64)
			{
				playerX = 1280 - 64;
			}
			if (playerY < 0)
			{
				playerY = 0;
			}
			if (playerY > 720 - 64)
			{
				playerY = 720 - 64;
			}

		}
		//Enemy処理
		{
			//移動
			enemyX += enemyMoveX;

			// 画面外に出ないようにする
			if (enemyX < 0)
			{
				enemyMoveX = 3;
				enemyX = 0;
			}
			if (enemyX > 1280 - 64)
			{
				enemyMoveX = -3;//移動の反転
				enemyX = 1280 - 64;
			}
		}



		/*描画の更新*/
		DrawGraph(playerX, playerY, playerGraph, FALSE);//Player描画
		DrawGraph(enemyX, enemyY, enemyGraph, FALSE);//敵を描画
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
	DxLib_End();//Dxlib終了処理
	return 0;//終了 
}