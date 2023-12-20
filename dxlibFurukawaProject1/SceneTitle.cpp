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
	// �O���t�B�b�N�ǂݍ���
	m_bgHandle = LoadGraph("data/image/bgTitle.jpg");
	assert(m_bgHandle != -1);

	// BGM�ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/BgmTitle.mp3");
	assert(m_bgmHandle != -1);

	// SE�ǂݍ���
	m_decideSe = LoadSoundMem("data/sound/TitleDecide.mp3");
	assert(m_decideSe != -1);

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// �t�F�[�h�C�������邽�߉���0����n�߂�
	ChangeVolumeSoundMem(0, m_bgmHandle);

	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneTitle::Update()
{

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)	// �p�b�h��1�{�^��or�L�[�{�[�h��Z�L�[
	{
		if (!m_isSceneEnd)
		{
			// ���ʉ��炷
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK);
		}

		// �^�C�g����ʂ��I������SceneMain�Ɉړ����鏈������������!
		m_isSceneEnd = true;
	}

	if (m_isSceneEnd)
	{
		// �t�F�[�h�A�E�g
		m_fadeAlpha += Game::kFadeSpeed;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		// �t�F�[�h�C��
		m_fadeAlpha -= Game::kFadeSpeed;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	// ��ʂ̃t�F�[�h�l�𗘗p���ăT�E���h�̉��ʂ����肷��
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);
}

void SceneTitle::Draw() const
{
	DrawGraph(0, 0, m_bgHandle, false);

	DrawString(120, 120, "�^�C�g�����", GetColor(0, 0, 0));
	DrawString(120, 120 + 48, "1�{�^��(Z)�������Ă�������", GetColor(0, 0, 0));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, Game::kScreenWidht, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// �s�����ɖ߂��Ă���
}

void SceneTitle::End()
{
	// BGM�̒�~
	StopSoundMem(m_bgmHandle);

	DeleteGraph(m_bgHandle);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_decideSe);
}