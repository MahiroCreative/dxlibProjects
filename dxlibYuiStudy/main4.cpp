#include "DxLib.h"

/*定数(kは定数Konstantを意味する)*/
namespace
{
	constexpr int ScreenSizeX = 1280;
	constexpr int ScreenSizeY = 720;
	constexpr int kShotNum = 20;//最大弾数
}

/*構造体宣言*/
//オブジェクトの位置
struct Position
{
	int x = 0;
	int y = 0;
};
//オブジェクトの大きさ
struct Size
{
	int w = 0;
	int h = 0;
};
//Player構造体(Player変数)
struct Player
{
	//画像・位置・サイズ
	int handle = -1;
	Position pos;
	Size size;
	//Shotを撃っている最中か
	bool isPrevshot = false;
};
//Enemy構造体(Enemy変数)
struct Enemy
{
	//画像・位置・サイズ
	int handle = -1;
	int damageHandle = -1;
	Position pos;
	Size size;
	//ダメージを受けている最中か
	bool isDamage = false;
	//ダメージを何回受けたか
	int damageCount = 0;
	//移動方向判定
	bool isRightMove = true;
};
//Shot構造体
struct Shot
{
	//画像・位置・サイズ
	int handle = -1;
	Position pos;
	Size size;
	//自分が存在しているか
	bool isExist = false;
};

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

	/*各構造体作成*/
	Player player;
	Enemy enemy;
	Shot shot[kShotNum];

	/*画像読み込み*/
	player.handle = LoadGraph("Resources/player.png");
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");
	int shotHandle = LoadGraph("Resources/shot.png");

	/*座標設定*/
	//Player
	player.pos.x = 288;
	player.pos.y = 400;
	//Enemy
	enemy.pos.x = 0;
	enemy.pos.y = 50;

	/*各オブジェクトのグラフィックサイズ*/
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);

	/*フラグ初期化*/
	//Player
	player.isPrevshot = false;
	//Enemy
	enemy.isDamage = false;
	enemy.damageCount = 0;
	enemy.isRightMove = true;
	//Shot
	for (int i = 0; i < kShotNum; i++)
	{
		// ショットのグラフィックをメモリにロード.
		shot[i].handle = shotHandle;
		// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
		shot[i].isExist = false;
		// 弾のグラフィックのサイズをえる
		shot[i].size.w = sizeW;
		shot[i].size.h = sizeH;
	}

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
				player.pos.y -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				player.pos.y += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				player.pos.x -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				player.pos.x += 3;
			}

			// 弾の発射処理(SPACE)
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
				if (player.isPrevshot == false)
				{
					// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
					for (int i = 0; i < kShotNum; i++)
					{
						// 弾iが画面上にでていない場合はその弾を画面に出す
						if (shot[i].isExist == false)
						{
							// 弾iの位置をセット、位置はプレイヤーの中心にする
							shot[i].pos.x = (player.size.w - shot[i].size.w) / 2 + player.pos.x;
							shot[i].pos.y = (player.size.h - shot[i].size.h) / 2 + player.pos.y;

							// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
							shot[i].isExist = true;

							// 一つ弾を出したので弾を出すループから抜けます
							break;
						}
					}
				}

				// 前フレームでショットボタンを押されていたかを保存する変数にtrue(おされていた)を代入
				player.isPrevshot = true;
			}
			else
			{
				// ショットボタンが押されていなかった場合は
				// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
				player.isPrevshot = false;
			}

			//画面外に出ないようにする
			if (player.pos.x < 0)
			{
				player.pos.x = 0;
			}
			if (player.pos.x > ScreenSizeX - player.size.w)
			{
				player.pos.x = ScreenSizeX - player.size.w;
			}
			if (player.pos.y < 0)
			{
				player.pos.y = 0;
			}
			if (player.pos.y > ScreenSizeY - player.size.h)
			{
				player.pos.y = ScreenSizeY - player.size.h;
			}
		}

		//Enemy処理
		{
			// エネミーの座標を移動している方向に移動する
			if (enemy.isRightMove == true)
			{
				enemy.pos.x += 3;
			}
			else
			{
				enemy.pos.x -= 3;
			}

			// 画面外に出ないようにし、端になったら反転
			if (enemy.pos.x > ScreenSizeX - enemy.size.w)
			{
				enemy.pos.x = ScreenSizeX - enemy.size.w;
				enemy.isRightMove = false;
			}
			else if (enemy.pos.x < 0)
			{
				enemy.pos.x = 0;
				enemy.isRightMove = true;
			}
		}

		//弾の処理
		for (int i = 0; i < kShotNum; i++)
		{
			// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
			if (shot[i].isExist == true)
			{
				// 弾iを１６ドット上に移動させる
				shot[i].pos.y -= 8;

				// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
				if (shot[i].pos.y < 0 - shot[i].size.h)
				{
					shot[i].isExist = false;
				}
			}

			// 弾のあたり判定.
			// 弾iが存在している場合のみ次の処理に映る
			if (shot[i].isExist == 1)
			{
				// エネミーとの当たり判定
				if (((shot[i].pos.x > enemy.pos.x && shot[i].pos.x < enemy.pos.x + enemy.size.w) ||
					(enemy.pos.x > shot[i].pos.x && enemy.pos.x < shot[i].pos.x + shot[i].size.w)) &&
					((shot[i].pos.y > enemy.pos.y && shot[i].pos.y < enemy.pos.y + enemy.size.h) ||
						(enemy.pos.y > shot[i].pos.y && enemy.pos.y < shot[i].pos.y + shot[i].size.h)))
				{
					// 接触している場合は当たった弾の存在を消す
					shot[i].isExist = 0;

					// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
					enemy.isDamage = true;

					// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
					enemy.damageCount = 0;
				}
			}
		}

		/*描画の更新(描画順がそのままレイヤー順)*/
		DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);//Player描画
		// エネミーを描画
		// 顔を歪めているかどうかで処理を分岐
		if (enemy.isDamage == true)
		{
			// 顔を歪めている場合はダメージ時のグラフィックを描画する
			DrawGraph(enemy.pos.x, enemy.pos.y, enemy.damageHandle, FALSE);

			// 顔を歪めている時間を測るカウンターに１を加算する
			enemy.damageCount++;

			// もし顔を歪め初めて ３０ フレーム経過していたら顔の歪んだ状態から
			// 元に戻してあげる
			if (enemy.damageCount == 30)
			{
				// 『歪んでいない』を表す
				enemy.isDamage = false;
			}
		}
		else
		{
			DrawGraph(enemy.pos.x, enemy.pos.y, enemy.handle, FALSE);
		}
		//弾の処理
		for (int i = 0; i < kShotNum; i++)
		{
			// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
			if (shot[i].isExist == true)
			{
				// 画面に弾iを描画する
				DrawGraph(shot[i].pos.x, shot[i].pos.y, shot[i].handle, FALSE);
			}
		}
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