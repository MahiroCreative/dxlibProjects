#include "DxLib.h"
#include "circlePlayer.h"
#include "circleEnemy.h"

namespace
{
	// 敵の数
	constexpr int kEnemyNum = 3;
	// 敵の位置情報
	constexpr int kEnemyIntervalX = 160;
	//色
	const unsigned int kRedColor = GetColor(255, 0, 0);
	const unsigned int kWhiteColor = GetColor(255, 255, 255);
}

void DispPlayerPos(Player& player)
{
	int x = player.GetPosX();
	int y = player.GetPosY();

	DrawFormatString(8, 460, GetColor(255, 255, 255), "(%3d, %3d)", x, y);
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

	Player player;
	player.Init();

	Enemy enemy[kEnemyNum];

	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i].Init();
	}

	int liveTime = GetNowCount();
	bool isFlag = true;

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		if (player.isExist())
		{
			// ゲームの処理
			player.Update();
			for (int i = 0; i < kEnemyNum; i++)
			{
				enemy[i].Update();
				player.Collision(enemy[i], kEnemyNum);
			}

			// 描画
			for (int i = 0; i < kEnemyNum; i++)
			{
				enemy[i].Draw();
			}
			player.Draw();

			DispPlayerPos(player);

			int time = (enemy[0].GetDelayChangTime() - (GetNowCount() - enemy[0].GetChangTime()));
			DrawFormatString(400, 0, kRedColor, "スピード変化まで%d.%d", time / 1000, time % 1000);
		}
		else
		{
			if (isFlag)
			{
				liveTime = GetNowCount() - liveTime;
				isFlag = false;
			}
			DrawFormatString(280, 220, kWhiteColor, "生き残っていた時間 %02d:%02d.%02d", liveTime / 60000, liveTime / 1000, liveTime % 1000);
			DrawString(280, 240, "R   ：リスタート", kWhiteColor);
			DrawString(280, 260, "ESC ：終了", kWhiteColor);
			if (CheckHitKey(KEY_INPUT_R))
			{
				liveTime = GetNowCount();
				isFlag = true;
				player.Init();
				for (int i = 0; i < kEnemyNum; i++)
				{
					enemy[i].Init();
				}
			}
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

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}