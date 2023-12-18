#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "Enemy1.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(kScreenSizeX, kScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	// グラフィックリソースのロード
//	int enemyHandle = LoadGraph("data/teki.png");	// ファイル名間違い
	int enemyHandle = LoadGraph("data/enemy.png");
	assert(enemyHandle != -1);	// ファイルのロードに失敗すると止まる

	Enemy enemy[kEnemyNum];
	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i].Init();
		enemy[i].SetHandle(enemyHandle);
		enemy[i].SetStartPos();
	}

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].Update();
		}

		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].Draw();
		}

		// 画面が切り替わるのを待つ
		ScreenFlip();

		//FPS固定(16.66ms)
		while (GetNowHiPerformanceCount() - start < 16667) {}

		/*割り込み処理(Esc:終了処理)*/
		if (ProcessMessage() < 0)
		{
			//マイナスの値（エラー値）が返ってきたらループを抜ける
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			//Escでも抜ける
			break;
		}
	}


	/*Dxlib終了処理*/
	DeleteGraph(enemyHandle);//グラフィックをメモリから解放
	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了
}