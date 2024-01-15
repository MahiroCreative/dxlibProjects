#include <memory>
#include "DxLib.h"
#include "GameCommon.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "RankingScene.h"

//Dxlibのエントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*定数*/
	//画面サイズ
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ

	/*変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*Sceneの作成*/
	auto p_titleScene = std::make_unique<TitleScene>();
	auto p_gameScene = std::make_unique<GameScene>();
	auto p_rankingScene = std::make_unique<RankingScene>();

	/*ゲームループ部*/
	//Scene変数
	SceneKind nowScene = SceneKind::TITLESCENE;
	SceneKind nextScene = SceneKind::TITLESCENE;
	//gameRoop.
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*ゲーム処理部*/
		if (nowScene == SceneKind::TITLESCENE)
		{
			//入出力処理
			MyKeyInput::Update();
			//計算処理
			nextScene = p_titleScene->Update();
			//描画処理
			p_titleScene->Draw();
		}
		else if (nowScene == SceneKind::GAMESCENE)
		{
			//入出力処理
			MyKeyInput::Update();
			//計算処理
			nextScene = p_gameScene->Update();
			//描画処理
			p_gameScene->Draw();
		}
		else if (nowScene == SceneKind::RANKING)
		{
			//入出力処理
			MyKeyInput::Update();
			//計算処理
			nextScene = p_rankingScene->Update();
			//描画処理
			p_rankingScene->Draw();
		}
		else if (nowScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}

		/*Scene変更初期化処理*/
		if (nextScene != nowScene)
		{
			//シーン切り替え
			nowScene = nextScene;
			//それぞれのシーンの初期化処理
			if (nowScene == SceneKind::TITLESCENE)
			{
				nowScene;
			}
			else if(nowScene == SceneKind::RANKING)
			{
				nowScene;
			}
		}


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