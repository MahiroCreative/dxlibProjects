#include <DxLib.h>
#include <cassert>
#include "SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib開始処理*/
	ChangeWindowMode(true);
	SetGraphMode(Game::kScreenWidht, Game::kScreenHeight, 32);
	if (DxLib_Init() == -1) { return -1; }
	SetDrawScreen(DX_SCREEN_BACK);

	/*シーンマネージャーの作成*/
	SceneManager scene;
	scene.Init();

	/*ゲームループ*/
	while (ProcessMessage() != -1)
	{
		//タイマーの作成と更新(起動時からの時間が入る)
		LONGLONG start = GetNowHiPerformanceCount();

		//画面クリア
		ClearDrawScreen();

		//処理更新
		scene.Update();

		//画面更新
		scene.Draw();

		//画面更新の確定
		ScreenFlip();

		//escKeyの確認(ループ脱出)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		//フレームレートの固定(FPS6016.66ms)
		while (GetNowHiPerformanceCount() - start < 16667);
	}

	/*シーンの終了処理*/
	scene.End();

	/*Dxlib終了*/
	DxLib_End();
	return 0;
}