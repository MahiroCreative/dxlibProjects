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
// 前回まで無理やりグローバル変数などでやっていたことを多少効率化しています。
// 【例：】
// ・シーン管理をポインタでちょっとだけスマートに
// ・弾丸など複数存在するデータを配列で一括管理
// ・エネミー/プレイヤー/弾丸のパラメータデータを構造体で１つに纏める
// ・ポンタはシーン管理に利用(返り値でのやり方と効率は変わらない)
// ・Input系はポインタと構造体を使用している。
// ・ポインタの使用で多重ループ構造の解消
// シーンの切り替えは前回同様実行メソッドを切り替える事でシーン管理をしています。
// また、シーン管理には列挙型を用いています。
//【ループ構造改善：】
//　前回までの構造だとシーン毎にゲームループが存在し、Mainループ中にシーンループがあり多重ループが発生している。
//　多重ループ構造はなるべく改善すべきである上に、ループの中にループある環境によってfpsが安定しない。
//　そのためループ構造の解消を行うためにオブジェクト座標系のポインタの乱用が発生している。

/*ゲームの仕様*/
//・タイトル画面
//	-START : ゲームシーンに移動
//  -RANK: ランキングシーンに移動
//	-END : ゲーム終了
//・ゲームシーン
// - Player :WASDで動く。マウス左クリックで弾を発射する。エネミーの弾が当たるとタイトルに戻る。弾は連射できる。
// - Enemy:上下に動く。一定間隔で弾を発射。撃つたびに弾の速度が早くなる。プレイヤーの弾が当たるとスコアが上昇する。弾が当たってる間は色が変わる。弾丸を一度に複数はなてる。
// - Score:右上に表示。現在のスコアが表示される。
//・ランキングシーン
// - ゲームを起動している間のMAXSCOREが表示される。ゲームを終了すると値は0に戻る。

/*注意*/
//fpsの差による挙動の違いは考慮していません。
//環境により、オブジェクトの速度などが変わってしまいます。

/*Scene種類管理用*/
enum SceneKind
{
	GAMEENED,
	TITLESCENE,
	GAMESCENE,
	RANKINGSCENE
};

/*Scene管理*/
struct SceneManager
{
	SceneKind _backScene = SceneKind::TITLESCENE;
	SceneKind _nextScene = SceneKind::TITLESCENE;
};

/*Input管理*/
struct KeyInput
{
	bool isInputEnterHold = false;//Enter用の変数
	bool isInputUpHold = false;//Up用の変数
	bool isInputDownHold = false;//Down用の変数
};

/*各シーン用の変数作成*/
//Player
struct Player
{
	int X;
	int Y;
	int R;
};
//Enemy
struct Enemy
{
	int X;
	int Y;
	int R;
};
//EnemyBullet
struct PlayerBullet
{
	int X;
	int Y;
	int R;
};
//PlayerBullet
struct EnemyBullet
{
	int X;
	int Y;
	int R;
};
//Score
struct Score
{
	int NowScore;
	int MaxScore;
};
//Timer
struct FrameCount
{
	int count;
};
//グローバル変数
constexpr int MAXPLAYERBULLET = 3;
constexpr int MAXENEMYBULLET = 8;

/*プロトタイプ宣言*/
void AllSceneInit(Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score);
void TitleScene(SceneManager* _sceneManager);
void GameScene(SceneManager* _sceneManager, Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score);
void RankingScene(SceneManager* _sceneManager, Score* _score);


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

	/*Dxlib初期化*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//画面サイズと解像度
	ChangeWindowMode(true);//Windowモード
	if (DxLib_Init() == -1) { return -1; }//Dxlib初期化
	SetDrawScreen(DX_SCREEN_BACK);//ダブルバッファリング

	/*ゲーム用変数の作成*/
	SceneManager sceneManager;
	Player player;
	Enemy enemy;
	PlayerBullet playerBullet[MAXPLAYERBULLET];
	EnemyBullet enemyBullet[MAXENEMYBULLET];
	Score score;

	/*ゲームループ部*/
	//gameRoop.
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*シーン初期化*/
		//シーン変更時に初期化
		if (sceneManager._backScene != sceneManager._nextScene)
		{
			AllSceneInit(&player, &enemy, playerBullet, enemyBullet, &score);
		}

		/*シーン遷移処理*/
		if (sceneManager._nextScene == SceneKind::TITLESCENE)
		{
			TitleScene(&sceneManager);
		}
		else if (sceneManager._nextScene == SceneKind::GAMESCENE)
		{
			GameScene(&sceneManager, &player, &enemy, playerBullet, enemyBullet, &score);
		}
		else if (sceneManager._nextScene == SceneKind::RANKINGSCENE)
		{
			RankingScene(&sceneManager, &score);
		}
		else if (sceneManager._nextScene == SceneKind::GAMEENED)
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

/*各シーン*/
void AllSceneInit(Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet,Score* _score)
{

}
void TitleScene(SceneManager* _sceneManager)
{
	/*ローカル変数*/

	//タイトルロゴ
	SetFontSize(80);//フォントサイズ変更
	DrawString(440, 240, "DxlibGame", GetColor(255, 255, 255));
	SetFontSize(40);//フォントサイズ上
	DrawString(460, 320, "-GameTemplate2-", GetColor(255, 255, 255));
	SetFontSize(20);//フォントサイズ初期化
	//ゲームシーンテキスト
	DrawString(600, 440, "START", GetColor(255, 255, 255));
	//ゲームエンドテキスト
	DrawString(600, 480, "END", GetColor(255, 255, 255));


	/*DebugDraw処理*/
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//シーン名表示
}
void GameScene(SceneManager* _sceneManager, Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score)
{

}
void RankingScene(SceneManager* _sceneManager, Score* _score)
{

}

/*Input関数*/
//Enterが押されたかどうかを判定する関数
bool InputEnter(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && !_Key->isInputEnterHold)
	{
		_Key->isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		_Key->isInputEnterHold = false;
	}

	return false;
}
//Upが押されたかどうかを判定する関数
bool InputUp(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_UP) && !_Key->isInputDownHold)
	{
		_Key->isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		_Key->isInputDownHold = false;
	}

	return false;
}
//Downが押されたかどうかを判定する関数
bool InputDown(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_DOWN) && !_Key->isInputUpHold)
	{
		_Key->isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		_Key->isInputUpHold = false;
	}

	return false;
}