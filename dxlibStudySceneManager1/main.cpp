#include "DxLib.h"
#include <math.h>

using namespace DxLib;

/*概要*/
//C言語の『関数まで』で組んだシーン管理(シーンマネージャー)
//分からない学生はCの『基礎文法』を復習してください。

/*構造*/
//それぞれのシーンを関数(メソッド)として分割して、
//実行するメソッドを切り替える事でシーン管理をしている。

/*注意*/
//fpsの差による挙動の違いは考慮していません。
//環境により、オブジェクトの速度などが変わってしまいます。

/*グローバル変数*/
//定数
constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int GAMESCENE = 2;
//int変数
int MaxScore = 0;
//bool変数
bool isInputEnterHold = false;//InputEnter用の変数
bool isInputUpHold = false;//InputUp用の変数
bool isInputDownHold = false;//InputDown用の変数

/*プロトタイプ宣言*/
//定義はMainの下。
int TitleScene();//タイトルシーン
int GameScene();//ゲームシーン
bool InputEnter();//Enterが押されたかどうかを判定する関数
bool InputUp();//Upが押されたかどうかを判定する関数
bool InputDown();//Downが押されたかどうかを判定する関数


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
	int nextScene = TITLESCENE;

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

/*シーン定義*/
//タイトル画面を実行するシーン。
//返り値で次に実行するシーンを指定する。
int TitleScene()
{
	/*変数*/
	bool gameRoop = true;
	int nextScene = TITLESCENE;
	int arrowPosY = 440;

	/*ゲーム処理*/
	while (gameRoop)
	{

		/*計算処理*/
		//Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
			
		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		//タイトルロゴ
		SetFontSize(80);//フォントサイズ上昇
		DrawString(460, 240, "DxlibGame", GetColor(255, 255, 255));
		SetFontSize(20);//フォントサイズ初期化

		//ゲームシーンテキスト
		DrawString(600, 440, "START", GetColor(255, 255, 255));

		//ゲームエンドテキスト
		DrawString(600, 480, "END", GetColor(255, 255, 255));

		//矢印
		DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));

		//DebugDraw処理
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//シーン名表示

		//裏画面を表へ
		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY ==440)
			{
				return GAMESCENE;
			}
			else
			{
				return GAMEEND;
			}

		}
	}

	//例外処理
	return TITLESCENE;
}
//ゲーム画面を実行するシーン。
//返り値で次に実行するシーンを指定する。
int GameScene()
{
	/*変数*/
	bool gameRoop = true;
	bool isShot = false;
	bool isHitEnemy = false;
	bool isHitPlayer = false;
	int nextScene = GAMESCENE;
	int playerHandle = LoadGraph("Chara.png");
	int playerPosX = 100;
	int playerPosY = 300;
	int playerColR = 14;
	int enemyPosX = 1200;
	int enemyPosY = 360;
	int enemyColR = 240;
	int bulletPosX = playerPosX;
	int bulletPosY = playerPosY;
	int bulletR = 8;
	int playerSpeed = 3;
	int bulletSpeed = 8;
	int score = 0;

	/*ゲーム処理*/
	while (gameRoop)
	{

		/*計算処理*/
		//player操作
		playerPosY -= CheckHitKey(KEY_INPUT_W) * playerSpeed;//up
		playerPosY += CheckHitKey(KEY_INPUT_S) * playerSpeed;//down
		playerPosX += CheckHitKey(KEY_INPUT_D) * playerSpeed;//right.
		playerPosX -= CheckHitKey(KEY_INPUT_A) * playerSpeed;//left.
		//shot操作
		if (isShot == false)
		{
			if (GetMouseInput() == MOUSE_INPUT_LEFT) isShot = true;
		}
		//bullet位置更新
		if (isShot)
		{
			bulletPosX = bulletPosX + bulletSpeed;
		}
		else
		{
			bulletPosX = playerPosX;
			bulletPosY = playerPosY;
		}
		//bullet位置初期化
		if(bulletPosX>1280)
		{
			isShot = false;
			bulletPosX = playerPosX;
			bulletPosY = playerPosY;
		}

		//エネミーの当たり判定
		int delX = bulletPosX - enemyPosX;
		int delY = bulletPosY - enemyPosY;
		int Length = (int)sqrt(delX*delX + delY*delY);//エネミーと弾の距離
		if (bulletR + enemyColR > Length)
		{
			isHitEnemy = true;
		}
		else
		{
			isHitEnemy = false;
		}
		//プレイヤーの当たり判定


		//スコアの更新
		if (isHitEnemy)
		{
			score++;
		}

		//ハイスコアの更新
		if (score < MaxScore)
		{
			MaxScore = score;
		}


		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		//player
		DrawRotaGraph(playerPosX,playerPosY,1,0,playerHandle,true);//指定した位置に画像の中心が来る
		//bullet.
		if (isShot)
		{
			DrawCircle(bulletPosX, bulletPosY, bulletR, GetColor(255, 0, 0), 1);
		}
		//enemy
		if (isHitEnemy)
		{
			DrawCircle(enemyPosX, enemyPosY, 240, GetColor(0, 255, 255), 1);
		}
		else
		{
			DrawCircle(enemyPosX, enemyPosY, 240, GetColor(0, 0, 255), 1);
		}
		//score
		DrawFormatString(10, 700, GetColor(0, 255, 255), "Score:%d", score);

		//DebugDraw処理
		DrawString(0, 0, "GameScene:WASDで操作", GetColor(255, 255, 255));//シーン名表示
		DrawCircle(playerPosX,playerPosY,playerColR,GetColor(0,255,0),0);//PlayerCol
		DrawCircle(enemyPosX, enemyPosY, enemyColR, GetColor(0, 255, 0), 0);//enemyCol

		//裏画面を表へ
		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			return TITLESCENE;
		}

	}

	//例外処理
	return TITLESCENE;
}

/*Input関数*/
//Enterが押されたかどうかを判定する関数
//Enterしか分からずイケてない。当然今後作り直していきます。
bool InputEnter()
{
	//指定フレーム以上押していたら押した判定
	if (CheckHitKey(KEY_INPUT_RETURN) && !isInputEnterHold)
	{
		isInputEnterHold = true;
		return true;
	}
	else if(!CheckHitKey(KEY_INPUT_RETURN))
	{
		isInputEnterHold = false;
	}

	return false;
}
//Upが押されたかどうかを判定する関数
//Upしか分からずイケてない。当然今後作り直していきます。
bool InputUp()
{
	//指定フレーム以上押していたら押した判定
	if (CheckHitKey(KEY_INPUT_UP) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		isInputDownHold = false;
	}

	return false;
}
//Downが押されたかどうかを判定する関数
//Downしか分からずイケてない。当然今後作り直していきます。
bool InputDown()
{
	//指定フレーム以上押していたら押した判定
	if (CheckHitKey(KEY_INPUT_DOWN) && !isInputUpHold)
	{
		isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		isInputUpHold = false;
	}

	return false;
}