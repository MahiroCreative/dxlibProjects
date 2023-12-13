#include "DxLib.h"

/*定数(kは定数Konstantを意味する)*/
namespace
{
	constexpr int kShotNum = 3;//画面上の最大弾数
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(1280, 720, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*リソース読み込み*/
	int playerGraph = LoadGraph("Resources/player.png");//Player
	int enemyGraph = LoadGraph("Resources/enemy.png");//Enemy
	int shotGraph = LoadGraph("Resources/shot.png");//Shot

	/*Playerセッティング*/
	//初期位置
	int playerX = 280;
	int playerY = 400;

	/*Enemyセッティング*/
	//初期位置
	int enemyX = 0;
	int enemyY = 50;
	bool enemyRightMove = true;//エネミーが右移動しているかどうか

	/*Shotセッティング*/
	//位置の初期化
	int shotX[kShotNum] = { 0 };
	int shotY[kShotNum] = { 0 };
	bool shotFlag[kShotNum] = { false };//Shotが存在するか

	/*Other*/
	bool isHitSpace = false;//前回キーが押されているか

	/*ゲームループ*/
	while (1)
	{
		/*画面初期化*/
		ClearDrawScreen();

		/*ゲーム処理*/
		//Player処理
		{
			//Key入力による移動
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				playerY -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				playerY += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				playerX -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				playerX += 3;
			}

			// 弾の発射処理(SPACE)
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				//Spaceが押されっぱなしでないなら、出る。
				if (!isHitSpace)
				{
					//Space押されっぱなしを検知するフラグ
					isHitSpace = true;

					//弾の生成処理
					for (int i = 0; i < kShotNum; i++)
					{
						// 弾は最大3発なので、余ってる枠があればそこに生成
						if (shotFlag[i] == false)
						{
							int Bw, Bh, Sw, Sh;

							// プレイヤーと弾の画像のサイズを得る
							GetGraphSize(playerGraph, &Bw, &Bh);
							GetGraphSize(shotGraph, &Sw, &Sh);

							// 弾iの位置をセット、位置はプレイヤーの中心にする
							shotX[i] = (Bw - Sw) / 2 + playerX;
							shotY[i] = (Bh - Sh) / 2 + playerY;

							// 弾iは現時点を持って存在するのでフラグを立てる。
							shotFlag[i] = true;

							break;
						}
					}
				}
			}
			else
			{
				//Spaceが押されていないなら、フラグを戻す。
				isHitSpace = false;
			}

			//画面外に出ないようにする
			if (playerX < 0)
			{
				playerX = 0;
			}
			if (playerX > 1280 - 64)
			{
				playerX = 1280 - 64;
			}
			if (playerY < 0)
			{
				playerY = 0;
			}
			if (playerY > 720 - 64)
			{
				playerY = 720 - 64;
			}
		}

		//Enemy処理
		{
			// エネミーの座標を移動している方向に移動する
			if (enemyRightMove == true)
			{
				enemyX += 3;
			}
			else
			{
				enemyX -= 3;
			}

			// 画面外に出ないようにし、端になったら反転
			if (enemyX > 1280 - 64)
			{
				enemyX = 1280 - 64;
				enemyRightMove = false;
			}
			else if (enemyX < 0)
			{
				enemyX = 0;
				enemyRightMove = true;
			}
		}

		//Shot処理
		//弾の移動ルーチン(弾が存在している場合のみ処処理)
		for (int i = 0; i < kShotNum; i++)
		{
			if (shotFlag[i] == true)
			{
				// 弾iを8ドット上に移動させる
				shotY[i] -= 4;

				// 画面外に出た場合は存在をfalse(存在しない)にする
				if (shotY[i] < -80)
				{
					shotFlag[i] = false;
				}				
			}
		}

		/*描画の更新(描画順がそのままレイヤー順)*/
		//Shotの描画
		for (int i = 0; i < kShotNum; i++)//全ての弾枠に処理
		{
			if (shotFlag[i] == true) //存在している弾だけ描画
			{
				DxLib::DrawGraph(shotX[i], shotY[i], shotGraph, FALSE);
			}
		}
		DxLib::DrawGraph(playerX, playerY, playerGraph, FALSE);//Player描画
		DxLib::DrawGraph(enemyX, enemyY, enemyGraph, FALSE);//敵を描画
		DxLib::ScreenFlip();//裏で作成した画面を表に

		/*ループ終了処理*/
		if (ProcessMessage() < 0)//エラー処理
		{
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))//Escでも終了する
		{
			break;
		}
	}

	/*終了処理*/
	DxLib::DxLib_End();//Dxlib終了処理
	return 0;//終了
}