#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle() :
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_decideSe(-1),
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// グラフィック読み込み
	m_bgHandle = LoadGraph("data/image/bgTitle.jpg");
	assert(m_bgHandle != -1);

	// BGM読み込み
	m_bgmHandle = LoadSoundMem("data/sound/BgmTitle.mp3");
	assert(m_bgmHandle != -1);

	// SE読み込み
	m_decideSe = LoadSoundMem("data/sound/TitleDecide.mp3");
	assert(m_decideSe != -1);

	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// フェードインさせるため音量0から始める
	ChangeVolumeSoundMem(0, m_bgmHandle);

	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneTitle::Update()
{

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)	// パッドの1ボタンorキーボードのZキー
	{
		if (!m_isSceneEnd)
		{
			// 効果音鳴らす
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK);
		}

		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
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
	else
	{
		// フェードイン
		m_fadeAlpha -= Game::kFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	// 画面のフェード値を利用してサウンドの音量を決定する
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);
}

void SceneTitle::Draw() const
{
	DrawGraph(0, 0, m_bgHandle, false);

	DrawString(120, 120, "タイトル画面", GetColor(0, 0, 0));
	DrawString(120, 120 + 48, "1ボタン(Z)を押してください", GetColor(0, 0, 0));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, Game::kScreenWidht, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// 不透明に戻しておく
}

void SceneTitle::End()
{
	// BGMの停止
	StopSoundMem(m_bgmHandle);

	DeleteGraph(m_bgHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_decideSe);
}