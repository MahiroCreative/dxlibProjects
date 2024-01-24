#include "DxLib.h"
#include <math.h>

/*概要*/
//名称:DxlibGameTemplate1
//C言語の『配列/ポインタ/構造体』を使って組んだテンプレートです。
// 非常に簡易的ですが
// ・シーン遷移(グローバル変数とif文で実装)
// ・インプットシステム(グローバル変数の乱用により実装)
// ・円の当たり判定(ベクトルを使わずに実装)
// などを備えています。
// 作成するゲームの下地として使うよりは『読んで理解できるか？』で学習進度を確認してください。
// 教科書やDxlibのリファレンスを見ながらの理解で構いません。
// 分からない学生はCの学習をやり直してください。

/*構造*/
//『配列/ポインタ/構造体』を使用することで、
// 前回までグローバル変数で無理やりやっていたことを多少スマートにしています。
// 特に複数の返り値が欲しかった場面で使用しています。
// シーンの切り替えは前回同様実行メソッドを切り替える事でシーン管理をしています。
// また、シーン管理には列挙型を用いています。

/*注意*/
//fpsの差による挙動の違いは考慮していません。
//環境により、オブジェクトの速度などが変わってしまいます。


//Scene管理用
enum SceneKind
{
	GAMEENED,
	TITLESCENE,
	GAMESCENE
};

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
	SceneKind nextScene;//Scene管理用

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
		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == GAMESCENE)
		{

			nextScene = GameScene();
		}
		else if (nextScene == GAMEEND)
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