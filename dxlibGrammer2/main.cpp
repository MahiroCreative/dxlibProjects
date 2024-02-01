#include "DxLib.h"

/*概要*/
//この『Grammerシリーズ』ではDxLibの基礎的な使い方と考え方を段階的にやります。
//ただし、このシリーズで解説する内容は必要必要、というレベルです。抜けが出ます。
//Dxlibのリファレンスを頻繁に見て関数に意味などを確認しながら進めるのが正しい使い方です。
//【リファレンス】
// https://dxlib.xsrv.jp/dxfunc.html

/*今回の要素*/
//・DxLib
// 　- 円の当たり判定

//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*画像の読み込み*/
	int drawHandle = LoadGraph("Chara.png");

	/*変数*/
	//Player変数
	int pPosX = 100;
	int pPosY = 300;
	int pSpeed = 2;
	//Bullet変数
	int bPosX = pPosX;
	int bPosY = pPosY;
	int bR = 4;
	int bSpeed = 8;
	bool isBullet = false;
	//Enemy変数
	int ePosX = 1000;
	int ePosY = 360;
	int eR = 64;
	int eSpeed = 8;
	bool isHit = false;

	/*ゲームループ部*/
	//gameRoop.
	while (TRUE)
	{
		//裏画面の初期化
		ClearDrawScreen();

		/*Player処理*/
		//移動処理
		if (CheckHitKey(KEY_INPUT_W))//Wで上移動
		{
			pPosY -= pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_S))//Sで下移動
		{
			pPosY += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_D))//Dで右移動
		{
			pPosX += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_A))//Aで左移動
		{
			pPosX -= pSpeed;
		}

		/*Bullet処理*/
		//弾の発射
		if (CheckHitKey(KEY_INPUT_RETURN) && isBullet == false)//弾は一発しか発射できない
		{
			isBullet = true;
		}
		//弾の移動
		if (isBullet)
		{
			bPosX += bSpeed;
		}
		//弾の位置初期化
		if (bPosX > 1280)//画面外に出たら
		{
			bPosX = pPosX;
			bPosY = pPosY;
			isBullet = false;
		}

		/*Enemy処理*/



		/*Draw*/
		//キャラクタ描画
		//DrawGraph(pPosX, pPosY, drawHandle, 1);
		DrawRotaGraph();
		//弾の描画
		if (isBullet)
		{
			DrawCircle(bPosX, bPosY, bR, GetColor(255, 255, 255), 1);
		}
		//エネミー描画
		DrawCircle(ePosX, ePosY, eR, GetColor(255, 0, 255), 1);



		//裏画面を表へ
		ScreenFlip();

		//裏画面を表へ(ダブルバッファリング3)
		ScreenFlip();
		/*リフレッシュ処理(-1ならエラー)*/
		if (ProcessMessage() < 0) { break; }
	}

	/*終了処理*/
	DxLib_End();//Dxlib終了処理
	return 0;//終了 
}