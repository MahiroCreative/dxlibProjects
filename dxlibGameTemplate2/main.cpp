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

/*グローバル定数*/
constexpr int MAXPLAYERBULLET = 3;
constexpr int MAXENEMYBULLET = 8;

/*グローバル変数*/
int MaxScore = 0;

/*プロトタイプ宣言*/
void TitleScene(SceneKind* _nextScene);
void GameScene(SceneKind* _nextScene);
void RankingScene(SceneKind* _nextScene);


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

	/*シーン管理用*/
	SceneKind nextScene;
	//初期化
	nextScene = SceneKind::TITLESCENE;

	/*シーンループ部*/
	//gameRoop.
	while (gameRoop)
	{
		//ループ開始時刻の確保
		roopStartTime = GetNowHiPerformanceCount();

		//裏画面の初期化
		ClearDrawScreen();

		/*シーン遷移処理*/
		if (nextScene == SceneKind::TITLESCENE)
		{
			TitleScene(&nextScene);
		}
		else if (nextScene == SceneKind::GAMESCENE)
		{
			GameScene(&nextScene);
		}
		else if (nextScene == SceneKind::RANKINGSCENE)
		{
			RankingScene(&nextScene);
		}
		else if (nextScene == SceneKind::GAMEENED)
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

/*シーン関数*/
void TitleScene(SceneKind* _nextScene)
{
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

}
void GameScene(SceneKind* _nextScene)
{

}
void RankingScene(SceneKind* _nextScene)
{

}

/*Input関数*/
//Keyフラグ管理
struct IsKeyInput
{
	bool isInputEnterHold = false;//Enter用の変数
	bool isInputUpHold = false;//Up用の変数
	bool isInputDownHold = false;//Down用の変数
};
//Enterが押されたかどうかを判定する関数
bool InputEnter(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && !_isKey->isInputEnterHold)
	{
		_isKey->isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		_isKey->isInputEnterHold = false;
	}

	return false;
}
//Upが押されたかどうかを判定する関数
bool InputUp(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_UP) && !_isKey->isInputDownHold)
	{
		_isKey->isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		_isKey->isInputDownHold = false;
	}

	return false;
}
//Downが押されたかどうかを判定する関数
bool InputDown(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_DOWN) && !_isKey->isInputUpHold)
	{
		_isKey->isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		_isKey->isInputUpHold = false;
	}

	return false;
}