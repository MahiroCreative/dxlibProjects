#include <DxLib.h>
#include <cassert>
#include "Enemy1.h"

namespace
{
	constexpr int kEnemyNum = 5;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファリング
	SetDrawScreen(DX_SCREEN_BACK);

	// グラフィックリソースのロード
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

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		// 16.66ms(16667マイクロ秒)経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	// グラフィックリソースをメモリから解放
	DeleteGraph(enemyHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}