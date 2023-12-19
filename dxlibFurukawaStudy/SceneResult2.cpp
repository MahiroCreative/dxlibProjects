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
	// �O���t�̓ǂݍ��݁A�T�C�Y�̎擾
	m_gameOverHandle = LoadGraph("data/image/gameover.png");
	assert(m_gameOverHandle != -1);
	m_bgHandle = LoadGraph("data/image/bgResult.jpg");
	assert(m_bgHandle != -1);

	// �T�E���h�̓ǂݍ���
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
	if (pad & PAD_INPUT_2)	// �p�b�h��1�{�^��or�L�[�{�[�h��X�L�[
	{
		if (!m_isSceneEnd)
		{
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK);
		}

		// SceneResult��ʂ��I������SceneTitle�Ɉړ����鏈��
		m_isSceneEnd = true;
	}

	ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);

	if (m_isSceneEnd)
	{
		// �t�F�[�h�A�E�g
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}

		return;
	}
	else
	{
		// �t�F�[�h�C��
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
	DrawString(500, 600, "2�{�^��(X)�������Ă�������", GetColor(255, 255, 255));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenSizeX, kScreenSizeY, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// �s�����ɖ߂��Ă���
}

void SceneResult::End()
{
	StopSoundMem(m_bgmHandle);

	DeleteGraph(m_gameOverHandle);
	DeleteGraph(m_bgHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_decideSe);
}