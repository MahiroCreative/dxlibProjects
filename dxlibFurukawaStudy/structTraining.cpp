#include "DxLib.h"
#include "structEnemy.h"
#include "structPlayer.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(1);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 画像情報を読み取る
	int tempNoHitPlayreHandle = LoadGraph("data/noHitPlayer.png");
	int tempHitPlayerHandle = LoadGraph("data/hitPlayer.png");
	int tempEnemyHandle = LoadGraph("data/enemy.png");

	// プレイヤー関連の情報
	Player player;

	// プレイヤーの初期化
	initPlayer(&player, tempNoHitPlayreHandle, tempHitPlayerHandle);

	// 敵関連の情報
	Enemy enemy[ENEMY_NUM];

	// 敵の初期化
	initAllEnmey(enemy, tempEnemyHandle);

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// update
		updatePlayer(&player);

		// 敵のupdate
		updateAllEnemy(enemy);

		// プレイヤーの描画
		drawPlayer(player, CollisionDetection(player, enemy));

		// 敵の描画
		drawAllEnemy(enemy);

		// 条件付きコンパイルを利用して
		// Debug版でのみ実行される処理を実装する
#ifdef _DEBUG
		// プレイヤーの座標表示
		DrawFormatString(8, 8, GetColor(2255, 255, 255), "Player(%f, %f)", player.x, player.y);
#endif	// _DEBUG

		// 画面が切り替わるのを待つ
		ScreenFlip();
	}

	DeleteGraph(tempNoHitPlayreHandle);
	DeleteGraph(tempHitPlayerHandle);
	DeleteGraph(tempEnemyHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}