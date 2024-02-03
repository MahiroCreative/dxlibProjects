#include "DxLib.h"

/*概要*/
//この『Grammerシリーズ』ではDxLibやゲームプログラミングの基礎的な使い方と考え方を段階的にやります。
//解説する内容は必要最低限です。抜けが出ます。また詳細な解説をしていません。
//随時リファレンスや外部サイトを参考にしてください。
//【リファレンス】
// https://dxlib.xsrv.jp/dxfunc.html

/*今回の要素*/
//・ゲームプログラミング
// 　- 複数オブジェクトの制御
//   - 類似処理の関数化
//   - コリジョンのデバッグ表示
//・C/C++言語
//   - グローバル変数
// 　- 定数(constexpr)
//   - 構造体変数の簡単な初期化
// 　- Roop文(for文)
//   - 配列
//   - 関数

/*構造体の作成(グローバル変数として構造体を作成)*/
//構造体をグローバル変数として作成する。Mainの外に記述すればよい。
//グローバル変数として作成することで、Main以外のメソッドでも使用することができる。
//また、作成時点で初期化することも可能.(NULLを入れているが、計算上は0として使われます)
struct GameObject
{
	int DrawHandle = NULL;//画像ハンドル
	int X = NULL;//X座標
	int Y = NULL;//Y座標
	int R = NULL;//半径
	int Speed = NULL;//速度
	int ShotCount = NULL;//現在発射している弾の数
	double Scale = NULL;//スケール
	double Rotate = NULL;//回転度
	unsigned int Color = NULL;//色
	unsigned int HitColor = NULL;//Hit時の色
	bool IsHit = NULL;//当たり判定用のフラグ
};

/*関数*/
//類似機能は関数としてまとめてしまう。
//プロトタイプ宣言しておくことで、後から処理を記述しても使えるようになる。
//プロトタイプ宣言.
bool IsHitCollision(GameObject _hitObj, GameObject _Bullets[]);//第一引数と第二引数群が当たったかを判定
void Draw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[]);//画面表示
void DebugDraw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[]);//Debug表示


//Dxlibのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*定数*/
	//プログラムの実行後に変更する可能性が無い数値は、定数として確保すべきである。
	// 定数の作り方は、『#define』や『const』など色々あるが、
	// 単なる定数として扱うなら『constexpr』が一番問題を起こさない可能性が高い。
	// その他の定数は必要になった際に学習して使用すればよい。
	//画面サイズ.
	constexpr int SCREEN_SIZE_X = 1280;//幅
	constexpr int SCREEN_SIZE_Y = 720;//高さ
	//弾数
	constexpr int PLAYER_MAX_SHOT = 4;//プレイヤーの最大弾数
	constexpr int ENEMY_MAX_SHOT = 2;//Enemyの最大弾数

	/*変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib初期化*/
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*変数*/
	//Player.
	GameObject Player;
	Player.DrawHandle = LoadGraph("Chara.png");
	Player.X = 100;//x座標
	Player.Y = 300;//y座標
	Player.R = 2;//半径
	Player.ShotCount = 0;//現在発射している弾数
	Player.Speed = 2;//スピード
	Player.Scale = 1;//スケール
	Player.Rotate = 0;//回転度
	Player.HitColor = GetColor(255, 0, 0);//Hit色
	Player.IsHit = false;//当たり判定
	//PlayerBullet.
	GameObject pBullet[PLAYER_MAX_SHOT];
	//PlayerBulletの初期化
	for (int i=0;i<PLAYER_MAX_SHOT;i++)
	{
		pBullet[i].X = Player.X;
		pBullet[i].Y = Player.Y;
		pBullet[i].R = 4;
		pBullet[i].Speed = 8;
		pBullet[i].Color = GetColor(255,255,255);
	}
	//Enemy.
	GameObject Enemy;
	Enemy.X = 1000;
	Enemy.Y = 360;
	Enemy.R = 80;
	Enemy.Speed = 1;
	Enemy.Color = GetColor(255, 0, 255);
	Enemy.HitColor = GetColor(0, 0, 255);
	Enemy.IsHit = false;
	//EnemyBullet.
	GameObject eBullet[ENEMY_MAX_SHOT];
	//PlayerBulletの初期化
	for (int i = 0; i < ENEMY_MAX_SHOT; i++)
	{
		eBullet[i].X = Enemy.X;
		eBullet[i].Y = Enemy.Y;
		eBullet[i].R = 32;
		eBullet[i].Speed = 8;
		eBullet[i].Color = GetColor(255, 255, 255);
	}


	/*ゲームループ部*/
	//gameRoop.
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*ゲーム処理部*/

		/*Draw*/
		Draw(Player,Enemy,pBullet,eBullet);

		/*DebugDraw*/
		DebugDraw(Player, Enemy, pBullet, eBullet);

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


/// <summary>
/// Dxlibを用いて画面表示を行う関数。
/// </summary>
void Draw()
{

}
/// <summary>
/// Dxlibを用いて画面表示を行う関数(Debug用)。
/// </summary>
void Draw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[])
{

}