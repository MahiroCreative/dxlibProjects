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

	/*画像の読み込み*/
	int drawHandle = LoadGraph("Chara.png");

	//変数
	int posX=100;
	int posY=300;

	/*ゲームループ部*/
	while (TRUE)
	{
		//裏画面の初期化(ダブルバッファリング1)
		ClearDrawScreen();

		/*Key入力の取得*/
		//CheckHitKeyに対応キーの数値を入れることで使う(詳細はリファレンス)。
		//今回はEnterが押されたかどうかを取得。
		if (CheckHitKey(KEY_INPUT_UP))
		{

		}
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{

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