#include "DxLib.h"

/*概要*/
//この『Grammerシリーズ』ではDxLibの基礎的な使い方と考え方を段階的にやります。
//ただし、このシリーズで解説する内容は必要必要、というレベルです。抜けが出ます。
//また、初学者向けの解説のような事はしていません。使い方の例が書いてある程度です。
//分からない部分は自ら能動的に調べて下さい。
//Dxlibのリファレンスを頻繁に見て関数に意味などを確認しながら進めるのが正しい使い方です。
//【リファレンス】
// https://dxlib.xsrv.jp/dxfunc.html

/*今回の要素*/
//・DxLib
// 　‐ Key入力
//・C文法
//   - if文


/*Dxlibのエントリーポイント*/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング


	/*変数*/
	//計算などをする際に一時的値を保存するために使う。
	//どのような数字を扱うかによって型が変わる。
	//基本的には整数はint,実数はfloatと考えるとよい。
	int drawHandle;//整数型
	int posX = 400;
	int moveX = 1;


	/*画像の読み込み*/
	//メモリに読み込み、その位置を入れている。引数で与えるのはファイルのパス。
	//こういう物を画像ハンドルと言う。今回はプロジェクトフォルダ直下に入れている。
	drawHandle = LoadGraph("Chara.png");


	/*ゲームループ部*/
	//一般的なゲームは単位時間毎に何度も何度も表示を繰り返す事で表現されます。
	//これをゲームループと言います。これが通常のプログラミングとの大きな違いです。
	//ユーザが何もしなくてもリアルタイムで表示が変化するのがゲームなので、絶対に必要な機能となります。
	//特に何かアクションが無ければ無限にループする必要があるため、条件にはTRUEを入れて無限ループを作成します。
	while (TRUE)
	{

		//裏画面の初期化(ダブルバッファリング1)
		ClearDrawScreen();


		/*ゲーム処理部(ダブルバッファリング2)*/
		//円の表示
		DrawCircle(100, 100, 20, 200, 1, 1);//(x座標,y座標,半径,色,塗り潰すかどうか,表示するか)
		//線の表示
		DrawLine(200, 200, 300, 300, 200, 1);//(始点x,始点y,終点x,終点y,色,表示するか)
		//画像の表示
		DrawGraph(posX, 400, drawHandle, 1);//(x座標,y座標,読み込んだ画像のハンドル,表示するか)

		//画像の移動
		//左右に振幅運動をさせている。
		posX += moveX;
		if (posX > 1200)
		{
			moveX = -moveX;
		}
		else if (posX < 100)
		{
			moveX = -moveX;
		}


		//裏画面を表へ(ダブルバッファリング3)
		ScreenFlip();


		/*リフレッシュ処理(-1ならエラー)*/
		if (ProcessMessage() < 0) { break; }

	}

	/*終了処理*/
	DxLib_End();//Dxlib終了処理
	return 0;//終了 
}