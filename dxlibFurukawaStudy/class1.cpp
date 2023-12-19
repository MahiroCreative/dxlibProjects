#include "DxLib.h"

// 定数
namespace
{
	// 初期配置
	constexpr int kStartPosX = 320;
	constexpr int kStartPosY = 240;

	// 移動速度
	constexpr int kSpeed = 4;
}

class Player
{
public:
	// メンバ変数であることがわかるようにm_(ルールに従えばなんでもよいが)を先頭につける
	int m_handle;		// グラフィックハンドル
	int m_posX;		// 表示座標X
	int m_posY;		// 表示座標Y
	bool m_isTurn;	// 左右反転フラグ

	// コンストラクタ	メモリを確保した時点で勝手に呼ばれる関数
	Player();				// 引数無しコンストラクタ
	Player(int x, int y);	// 引数で初期位置を設定できるコンストラクタ

	// デストラクタ		メモリを解放した時点で勝手に呼ばれる関数
	~Player();

	// メンバ関数
	void Init();	// 初期化
	void Update();	// 毎フレームの更新
	void Draw();	// 描画
};

// Playerクラスのコンストラクト
// 引数無し
Player::Player()
{
	// グラフィックのロード
	m_handle = LoadGraph("data/player.png");

	m_posX = kStartPosX;
	m_posY = kStartPosY;

	// グラフィック反転フラグ
	m_isTurn = false;
}
// 引数あり
Player::Player(int x, int y)
{
	// グラフィックのロード
	m_handle = LoadGraph("data/player.png");

	m_posX = x;
	m_posY = y;

	// グラフィック反転フラグ
	m_isTurn = false;
}

// Playerクラスのデストラクタ
Player::~Player()
{
	// メモリが解放されるときに必ず呼んでほしい処理を書く
	DeleteGraph(m_handle);
}

// メンバ関数の実装
// 関数名の前にクラス名::　を書いてやってこのクラスのInit関数です、と宣言する
void Player::Init()
{
	//初期化処理
}

void Player::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_UP)
	{
		m_posY -= kSpeed;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		m_posY += kSpeed;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		m_posX -= kSpeed;
		m_isTurn = false;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_posX += kSpeed;
		m_isTurn = true;
	}
}

void Player::Draw()
{
	if (m_isTurn)
	{
		DrawTurnGraph(m_posX, m_posY, m_handle, false);
	}
	else
	{
		DrawGraph(m_posX, m_posY, m_handle, false);
	}
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファリング
	SetDrawScreen(DX_SCREEN_BACK);

	// プレイヤー
	Player player;				// 引数無しで宣言
	//	Player player2(500, 20);	// 引数ありで宣言	ちょっと古い
	Player player2{ 500, 20 };	// 引数ありで宣言	最新は波かっこ

	// プレイヤーの初期化
	player.Init();
	player2.Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		player.Update();
		player2.Update();

		// 描画
		player.Draw();
		player2.Draw();

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