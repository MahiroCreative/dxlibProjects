#include <DxLib.h>
#include <cassert>
#include <cmath>

/*概要*/
//サインコサインなど。

/// <summary>
/// 度数法で指定した角度を弧度法に変換する
/// </summary>
/// <param name="deg">度数法の角度</param>
/// <returns>弧度法の角度</returns>
double DegToRad(double deg)
{
	return DX_PI / 180 * deg;
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

	int handle = LoadGraph("data/arrow.png");
	assert(handle != -1);

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理

		// 円周率DXLIBが#defineで定義してくれているので
		// DxLibでゲームを作るときはそれを使おう！

		// DX_PI		double型
		// DX_PI_F		float型
		// DX_TWO_PI	DX_PIの2倍
		// DX_TWO_PI_F	DX_PI_Fの2倍

		// 0度から45度ずつ回転6つ描画
		for (int i = 0; i < 6; i++)
		{
			DrawRotaGraph(64 + 96 * i, 64,
				1.0,	// 拡大率
				DegToRad(i * 45.0),	// 回転
				handle, true, false);
		}



		for (int i = 0; i < 6; i++)
		{
			int startX = 64 + 96 * i;
			int startY = 64 + 128;

			// 中心点
			DrawCircle(startX,
				startY,
				2, 0xffff00, true);

			// 中心点から上に表示されている矢印と同じ方向に
			// 長さ32の線を引きたい

			// 線を伸ばす方向
			double angle = DegToRad(i * 45);
			double moveX = 32 * cosf(angle);
			double moveY = 32 * sinf(angle);

			int endX = startX + static_cast<int>(moveX);
			int endY = startY + static_cast<int>(moveY);
			DrawLine(startX, startY,
				endX,
				endY,
				0xffffff);
		}

		// 回転デモ
		{
			int startX = 320;
			int startY = 400;

			DrawBox(startX - 64, startY - 64,
				startX + 65, startY + 65,
				0xff0000, false);

			DrawCircle(startX, startY, 64,
				0x00ff00, false);


			// 中心点
			DrawCircle(startX,
				startY,
				2, 0xffff00, true);

			// tempAngleの方向に伸びる線を引く
			static double tempAngle = 0.0;
			tempAngle += 0.02;

			// 線が伸びる方向を取得する
			// cosでX成分、sinでY成分を取得する
			double moveX = 64 * cosf(tempAngle);
			double moveY = 64 * sinf(tempAngle);

			// 開始点の座標を足して終点の座標に
			int endX = startX + static_cast<int>(moveX);
			int endY = startY + static_cast<int>(moveY);

			DrawLine(startX, startY,
				endX,
				endY,
				0xffffff);
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

	DeleteGraph(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}