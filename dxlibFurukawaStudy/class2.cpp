#include "DxLib.h"
#include <cassert>

// クラス
class Enemy
{
	// メンバ変数、メンバ関数にはprivate,publicという属性がある
	// メンバ変数は全てprivate:にしましょう

#if true
// public:もprivate:書いていない場所に書いたメンバはprivateメンバ
	int m_pri000;	// privateメンバ

	// private:よりも後に書いたメンバ(変数、関数)はprivateメンバ
private:
	int m_pri001;	// privateメンバ

	// public:よりも後に書いたメンバ(変数、関数)はpublicメンバ
public:
	int m_pub000;	// publicメンバ

	void pubFunc();	// publicメンバの関数
	// private:,public: 何度書いてもよい
private:
	int m_pri002;	// privateメンバ
	void priFunc();	// privateメンバの関数
#endif

public:		// 外部からのアクセス可能にする

	// メンバ変数名はそのプログラムを見た人が見ただけでこれはメンバ変数、
	// と分かるように名前を付けることが多い
	// 変数名の前に m_ をつけたり、		handle -> m_handle
	// 変数名の前に _ をつけたり、		handle -> _handle
	// 変数名の最後に _ をつけたりする	handle -> handle_
	// ルールはどれでも構わないが、必ず統一して書く
	// チーム制作の場合はチームでどのようなルールにするか決める
	int m_handle;	// グラフィックハンドル
	int m_posX;		// X座標
	int m_posY;		// Y座標
	int m_moveX;	// X方向の移動座標
	int m_moveY;	// Y方向の移動座標

	// コンストラクタ
	// 実体が作成されたとき(メモリが確保されたとき)自動的に呼び出される関数
	// 戻り値無し、クラス名と同じ関数名
	Enemy();
	// デストラクタ
	// メモリが解放されたとき自動的に呼ばれる関数
	// 戻り値無し、引数も設定できない　関数名はクラス名の前に~(チルダ)を書く
	~Enemy();

	// クラスは構造体に加えてクラス内で関数を作成することができる
	// クラス内の関数をメンバ関数という
	void Init();
	void Update();
	void Draw();
};

#if true
void Enemy::pubFunc()
{

}

void Enemy::priFunc()
{

}
#endif

// Enemyクラスのコンストラクト
// コンストラクタで値を初期化したい場合は特別な書き方がある
// コンストラクタ初期化子という

// コンストラクタ初期化子に関して
// コンストラクタ初期化子を使っても使わなくても結果は同じ
// だがコンストラクタ初期化子を使う
// ・処理速度的に有利
// ・コンストラクタ初期化子分かってますアピール
Enemy::Enemy() :
	m_handle(-1),
	m_posX(320),
	m_posY(240),
	m_moveX(0),
	m_moveY(0)
{
	// 値を初期化したり、0クリアしたりする

	// メンバ関数から同じクラス内のメンバ変数にアクセスできる
	// アクセスする際はenemy.handle のような書き方をしなくても handle のみでアクセスできる

	// メンバ変数はコンストラクタ初期化子で初期化するようにする
	m_handle = LoadGraph("data/obj.png");
	assert(m_handle != -1);
}

// Enemyクラスのデストラクタ
Enemy::~Enemy()
{
	// 終了時に忘れずにやっておかないといけない処理を書く
	DeleteGraph(m_handle);
}

// メンバ関数を実装したいときは関数名の前に クラス名:: と書く
void Enemy::Init()
{

}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	// クラス内からならprivateメンバ、publicメンバ共にアクセス可能
	m_pub000 = 10;
	pubFunc();

	m_pri000 = 10;
	priFunc();

	DrawGraph(m_posX, m_posY, m_handle, false);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファリング
	SetDrawScreen(DX_SCREEN_BACK);

	Enemy enemy;

	// メンバ関数の呼び出し
	// メンバ変数と同じく . (ドット)でつないでメンバ関数を呼び出す
	enemy.Init();

	// publicメンバにはクラス外からアクセスできる
	// privateメンバにはクラス外からアクセスできない
	// クラス外？　そのクラスのメンバ関数内はクラス内。それ以外はクラス外
	// ここはEnemyクラスの外

	// public メンバにはアクセス可能、使用可能
	enemy.m_pub000 = 10;
	enemy.pubFunc();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理

		enemy.Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		// 16.66ms(16667マイクロ秒)経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}