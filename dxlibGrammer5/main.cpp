#include "DxLib.h"

/*概要*/
//この『Grammerシリーズ』ではDxLibやゲームプログラミングの基礎的な使い方と考え方を段階的にやります。
//解説する内容は必要最低限です。抜けが出ます。また詳細な解説をしていません。
//随時リファレンスや外部サイトを参考にしてください。
//【リファレンス】
// https://dxlib.xsrv.jp/dxfunc.html

/*今回の要素*/
//・ゲームプログラミング
// 　- Input処理(Key入力の拡張)
// 　- Draw(),DebgugDraw()の汎用性を高める。
//・C/C++言語
//   - 構造体でポリモーフィズムもどき

/*構造体の作成*/
//全てのオブジェクトを一つの構造体で作ることで、
//関数に渡す引数を減らしたり、返り値で受け取りやすくしたり、データのやり取りを単純化する。
//GameOject.
struct GameObject
{
	//全てのオブジェクトに対応できるように変数を沢山用意(とりあえず全部NULLで初期化)
	int DrawHandle = NULL;//画像ハンドル
	int X = NULL;//X座標
	int Y = NULL;//Y座標
	int R = NULL;//半径
	int Speed = NULL;//速度
	int MaxShotNum = NULL;//発射できる最大弾数
	int ShotCount = NULL;//現在発射している弾数
	unsigned int Color = NULL;//色
	unsigned int HitColor = NULL;//Hit色
	double Scale = NULL;//スケール
	double Rotate = NULL;//回転度
	bool IsShot = NULL;//弾を撃っているか
	bool IsHit = NULL;
	bool IsVisible = NULL;
};


//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*ゲームループ用変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//画面サイズと解像度
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