#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "Game.h"

namespace
{
	// 敵の初期生成間隔(フレーム数)
	constexpr int kEnemyWaitFrameDefault = 60;
	// 敵の最短生成間隔(フレーム数)
	constexpr int kEnemyWaitFrameMin = 3;
	// 敵の生成間隔を敵何体生成するたびに短くするか
	constexpr int kEnemyWaitFrameChangeNum = 5;
	// 一度生成間隔を短くするときに何フレーム短くするか
	constexpr int kEnemyWaitFrameChangeFrame = 1;

	// ゲームオーバー時に表示する文字列
	const char* const kGameOverString = "GameOver";
}

SceneMain::SceneMain() :
	m_playerHandle(-1),
	m_enemyHandle(-1),
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_enemyStartSe(-1),
	m_hitSe(-1),
	m_walkSe(-1),
	m_player(),
	m_enemy(),
	m_isGameOver(false),
	m_isSceneEnd(false),
	m_playFrameCount(0),
	m_enemyCreateNum(0),
	m_enemyWaitFrame(0),
	m_fadeAlpha(255)			// 不透明で初期化
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// フォントの変更
	ChangeFont("HG行書体");
	SetFontSize(48);

	// グラフの読み込み
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/image/bgMain.png");
	assert(m_bgHandle != -1);

	// サウンドの読み込み
	m_bgmHandle = LoadSoundMem("data/sound/BgmMain.mp3");
	assert(m_bgmHandle != -1);
	m_enemyStartSe = LoadSoundMem("data/sound/EnemyFall.mp3");
	assert(m_enemyStartSe != -1);
	m_hitSe = LoadSoundMem("data/sound/Hit.mp3");
	assert(m_hitSe != -1);
	m_walkSe = LoadSoundMem("data/sound/Walk.mp3");
	assert(m_walkSe != -1);

	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// フェードインさせるため音量0から始める
	ChangeVolumeSoundMem(0, m_bgmHandle);

	// プレイヤーの初期化
	m_player.SetGraphHandle(m_playerHandle);
	m_player.SetWalkSeHandle(m_walkSe);
	m_player.Init();

	// 敵の初期化
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetGraphHandle(m_enemyHandle);
		m_enemy[i].SetStartPos();
	}

	// 各種変数初期化
	m_isSceneEnd = false;
	m_isGameOver = false;
	m_playFrameCount = 0;
	m_enemyCreateNum = 0;
	m_enemyWaitFrame = 0;

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);

	// ゲームオーバーなら各処理を行わず、即Updateを終了させる
	if (m_isGameOver)
	{
		// 1ボタンorZキーが押されたらゲームオーバー画面へ
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)
		{
			m_isSceneEnd = true;
		}

		if (m_isSceneEnd)
		{
			// フェードアウト
			m_fadeAlpha += Game::kFadeSpeed;
			if (m_fadeAlpha > 255)
			{
				m_fadeAlpha = 255;
			}
		}

		return;
	}

	// フェードイン
	m_fadeAlpha -= Game::kFadeSpeed;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// 生き残り時間(フレーム数を増やす)
	m_playFrameCount++;

	m_player.Update();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Update();
		if (m_player.IsCollision(m_enemy[i]))
		{
			if (!m_isGameOver)
			{
				PlaySoundMem(m_hitSe, DX_PLAYTYPE_BACK);
			}

			m_isGameOver = true;
		}
	}

	// 一定間隔で敵を生成
	m_enemyWaitFrame++;

	// 敵を一定数生成するたびに敵の生成間隔が短くなる
	int waitFrame = kEnemyWaitFrameDefault;
	waitFrame -= (m_enemyCreateNum / kEnemyWaitFrameChangeNum) * kEnemyWaitFrameChangeFrame;
	// 一番短い生成間隔のチェック
	if (waitFrame < kEnemyWaitFrameMin)	waitFrame = kEnemyWaitFrameMin;

	if (m_enemyWaitFrame >= waitFrame)
	{
		// 現在使われていない敵キャラクターを探して
		// そいつをStartさせる
		for (int i = 0; i < kEnemyMax; i++)
		{
			// 条件に合うやつが存在していない
			// のでそいつを使う
			if (!m_enemy[i].IsExist())
			{
				m_enemyCreateNum++;

				// 生成カウントを初期化
				m_enemyWaitFrame = 0;

				m_enemy[i].Start();

				// 効果音鳴らす
				PlaySoundMem(m_enemyStartSe, DX_PLAYTYPE_BACK);

				break;	// 1体生産したら終了
			}
		}
	}
}

void SceneMain::Draw() const
{
	DrawGraph(0, 0, m_bgHandle, false);

	m_player.Draw();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Draw();
	}

	// 生存時間を表示
	// 分：秒．ミリ秒 1:05.0004
	int milliSec = m_playFrameCount * 1000 / 60;
	int sec = milliSec / 1000;
	int min = sec / 60;
	milliSec %= 1000;
	sec %= 60;

	// 文字列の横幅取得
	int strWidht = GetDrawFormatStringWidth("%3d:%02d.%03d", min, sec, milliSec);

	DrawFormatString(Game::kScreenWidht / 2 - strWidht / 2,
		Game::kScreenHeight - 64, GetColor(255, 255, 255),
		"%3d:%02d.%03d", min, sec, milliSec);

	if (m_isGameOver)
	{
		// 画面中央にゲームオーバー表示

		// 表示する文字列の横幅を取得する
		// 第一引数に調べたい文字列
		// 第二引数に調べたい文字列のBit数
		// 例："abcdefg"	の場合　7
		// 　　"あいうえお"	の場合　10
		int len = strlen(kGameOverString);
		int widht = GetDrawStringWidth(kGameOverString, len);
		int height = GetFontSize();

		DrawString(Game::kScreenWidht / 2 - widht / 2,
			Game::kScreenHeight / 2 - height / 2,
			kGameOverString, GetColor(255, 0, 0));
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, Game::kScreenWidht, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// 不透明に戻しておく
}

void SceneMain::End()
{
	// BGMの停止
	StopSoundMem(m_bgmHandle);

	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	// メモリからサウンドを削除
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_enemyStartSe);
	DeleteSoundMem(m_hitSe);
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
