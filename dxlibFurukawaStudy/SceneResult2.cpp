#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "SceneResult2.h"

SceneResult::SceneResult() :
	m_gameOverHandle(-1),
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_decideSe(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_lastPad(0),
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	// グラフの読み込み、サイズの取得
	m_gameOverHandle = LoadGraph("data/image/gameover.png");
	assert(m_gameOverHandle != -1);
	m_bgHandle = LoadGraph("data/image/bgResult.jpg");
	assert(m_bgHandle != -1);

	// サウンドの読み込み
	m_bgmHandle = LoadSoundMem("data/sound/bgmResult.mp3");
	assert(m_bgmHandle != -1);
	m_decideSe = LoadSoundMem("data/sound/TitleDecide.mp3");
	assert(m_decideSe != -1);

	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(0, m_bgmHandle);

	GetGraphSize(m_gameOverHandle, &m_graphWidth, &m_graphHeight);

	m_isSceneEnd = false;

	m_fadeAlpha = 255;
}

void SceneResult::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_2)	// パッドの1ボタンorキーボードのXキー
	{
		if (!m_isSceneEnd)
		{
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK);
		}

		// SceneResult画面を終了してSceneTitleに移動する処理
		m_isSceneEnd = true;
	}

	ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);

	if (m_isSceneEnd)
	{
		// フェードアウト
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}

		return;
	}
	else
	{
		// フェードイン
		m_fadeAlpha -= kFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneResult::Draw()
{
	DrawExtendGraph(0, 0, kScreenSizeX, kScreenSizeY, m_bgHandle, false);
	DrawGraph(kScreenSizeX / 2 - m_graphWidth / 2,
		kScreenSizeY / 2 - m_graphHeight / 2,
		m_gameOverHandle, true);
	DrawString(500, 600, "2ボタン(X)を押してください", GetColor(255, 255, 255));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenSizeX, kScreenSizeY, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// 不透明に戻しておく
}

void SceneResult::End()
{
	StopSoundMem(m_bgmHandle);

	DeleteGraph(m_gameOverHandle);
	DeleteGraph(m_bgHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_decideSe);
}