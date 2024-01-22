#include "DxLib.h"

/*概要*/
//C言語の機能のみで組んだシーン管理(シーンマネージャー)
//その中でも関数までで組んでいる。
//このレベルが分からない学生はCの文法を復習してください。

/*構造*/
//それぞれのシーンを関数(メソッド)として分割して、
//実行するメソッドを切り替える事でシーン管理をしている。


//プロトタイプ宣言
//定義はMainの下。
int TitleScene();
int GameScene();
bool InputKey(int KeyCode, int InputFrame);

/*グローバル変数*/
enum SceneKind//シーン管理用
{
	GAMEEND,
	TITLESCENE,
	GAMESCENE
};
int InputKeyTime = 0;//InputKey用のグローバル変数

//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*定数*/
	//画面サイズ
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ

	/*変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	int nextScene = SceneKind::TITLESCENE;

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*ゲームループ部*/
	//gameRoop.
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*ゲーム処理部*/
		//シーン管理
		if (nextScene == SceneKind::TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == SceneKind::GAMESCENE)
		{
			nextScene = GameScene();
		}
		else if (nextScene == SceneKind::GAMEEND)
		{
			break;
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

/*シーン定義*/
//タイトル画面を実行するシーン。
//返り値で次に実行するシーンを指定する。
int TitleScene()
{
	/*ゲーム処理*/


	/*Draw処理*/
	//タイトルロゴ
	SetFontSize(80);//フォントサイズ上昇
	DrawString(460, 240, "DxlibGame", GetColor(255, 255, 255));
	SetFontSize(20);//フォントサイズ初期化



	/*DebugDraw処理*/
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//シーン名表示


	/*シーン遷移処理*/
	//4フレーム以上Enterを押したらシーン変更
	if (InputKey(KEY_INPUT_RETURN, 4))
	{
		return SceneKind::GAMESCENE;
	}
	return SceneKind::TITLESCENE;
}
//ゲーム画面を実行するシーン。
//返り値で次に実行するシーンを指定する。
int GameScene()
{
	//シーン名の表示
	SetFontSize(80);//フォントサイズ上昇
	DrawString(420, 240, "GameScene", GetColor(255, 255, 255));
	SetFontSize(20);//フォントサイズ初期化

	//シーン変更処理
	//4フレーム以上Enterを押したらシーン変更
	if (InputKey(KEY_INPUT_RETURN,4))
	{
		return SceneKind::TITLESCENE;
	}

	return SceneKind::GAMESCENE;
}

/*関数*/
//Enterが押されたかどうかを判定する関数
//指定したフレーム以上押されたら押されたと判定する。
//理解しやすさを優先した一時的なものなので、当然今後作り直していきます。
bool InputKey(int KeyCode,int InputFrame)
{
	//4フレーム以上押していたら押した判定
	if (CheckHitKey(KeyCode) && InputKeyTime > InputFrame)
	{
		InputKeyTime = 0;
		return true;
	}
	else if (CheckHitKey(KeyCode))
	{
		InputKeyTime++;
	}

	return false;
}