#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "Game.h"

namespace
{
	// �G�̏��������Ԋu(�t���[����)
	constexpr int kEnemyWaitFrameDefault = 60;
	// �G�̍ŒZ�����Ԋu(�t���[����)
	constexpr int kEnemyWaitFrameMin = 3;
	// �G�̐����Ԋu��G���̐������邽�тɒZ�����邩
	constexpr int kEnemyWaitFrameChangeNum = 5;
	// ��x�����Ԋu��Z������Ƃ��ɉ��t���[���Z�����邩
	constexpr int kEnemyWaitFrameChangeFrame = 1;

	// �Q�[���I�[�o�[���ɕ\�����镶����
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
	m_fadeAlpha(255)			// �s�����ŏ�����
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �t�H���g�̕ύX
	ChangeFont("HG�s����");
	SetFontSize(48);

	// �O���t�̓ǂݍ���
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/image/bgMain.png");
	assert(m_bgHandle != -1);

	// �T�E���h�̓ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/BgmMain.mp3");
	assert(m_bgmHandle != -1);
	m_enemyStartSe = LoadSoundMem("data/sound/EnemyFall.mp3");
	assert(m_enemyStartSe != -1);
	m_hitSe = LoadSoundMem("data/sound/Hit.mp3");
	assert(m_hitSe != -1);
	m_walkSe = LoadSoundMem("data/sound/Walk.mp3");
	assert(m_walkSe != -1);

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// �t�F�[�h�C�������邽�߉���0����n�߂�
	ChangeVolumeSoundMem(0, m_bgmHandle);

	// �v���C���[�̏�����
	m_player.SetGraphHandle(m_playerHandle);
	m_player.SetWalkSeHandle(m_walkSe);
	m_player.Init();

	// �G�̏�����
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetGraphHandle(m_enemyHandle);
		m_enemy[i].SetStartPos();
	}

	// �e��ϐ�������
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

	// �Q�[���I�[�o�[�Ȃ�e�������s�킸�A��Update���I��������
	if (m_isGameOver)
	{
		// 1�{�^��orZ�L�[�������ꂽ��Q�[���I�[�o�[��ʂ�
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)
		{
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

		return;
	}

	// �t�F�[�h�C��
	m_fadeAlpha -= Game::kFadeSpeed;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// �����c�莞��(�t���[�����𑝂₷)
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

	// ���Ԋu�œG�𐶐�
	m_enemyWaitFrame++;

	// �G����萔�������邽�тɓG�̐����Ԋu���Z���Ȃ�
	int waitFrame = kEnemyWaitFrameDefault;
	waitFrame -= (m_enemyCreateNum / kEnemyWaitFrameChangeNum) * kEnemyWaitFrameChangeFrame;
	// ��ԒZ�������Ԋu�̃`�F�b�N
	if (waitFrame < kEnemyWaitFrameMin)	waitFrame = kEnemyWaitFrameMin;

	if (m_enemyWaitFrame >= waitFrame)
	{
		// ���ݎg���Ă��Ȃ��G�L�����N�^�[��T����
		// ������Start������
		for (int i = 0; i < kEnemyMax; i++)
		{
			// �����ɍ���������݂��Ă��Ȃ�
			// �̂ł������g��
			if (!m_enemy[i].IsExist())
			{
				m_enemyCreateNum++;

				// �����J�E���g��������
				m_enemyWaitFrame = 0;

				m_enemy[i].Start();

				// ���ʉ��炷
				PlaySoundMem(m_enemyStartSe, DX_PLAYTYPE_BACK);

				break;	// 1�̐��Y������I��
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

	// �������Ԃ�\��
	// ���F�b�D�~���b 1:05.0004
	int milliSec = m_playFrameCount * 1000 / 60;
	int sec = milliSec / 1000;
	int min = sec / 60;
	milliSec %= 1000;
	sec %= 60;

	// ������̉����擾
	int strWidht = GetDrawFormatStringWidth("%3d:%02d.%03d", min, sec, milliSec);

	DrawFormatString(Game::kScreenWidht / 2 - strWidht / 2,
		Game::kScreenHeight - 64, GetColor(255, 255, 255),
		"%3d:%02d.%03d", min, sec, milliSec);

	if (m_isGameOver)
	{
		// ��ʒ����ɃQ�[���I�[�o�[�\��

		// �\�����镶����̉������擾����
		// �������ɒ��ׂ���������
		// �������ɒ��ׂ����������Bit��
		// ��F"abcdefg"	�̏ꍇ�@7
		// �@�@"����������"	�̏ꍇ�@10
		int len = strlen(kGameOverString);
		int widht = GetDrawStringWidth(kGameOverString, len);
		int height = GetFontSize();

		DrawString(Game::kScreenWidht / 2 - widht / 2,
			Game::kScreenHeight / 2 - height / 2,
			kGameOverString, GetColor(255, 0, 0));
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, Game::kScreenWidht, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			// �s�����ɖ߂��Ă���
}

void SceneMain::End()
{
	// BGM�̒�~
	StopSoundMem(m_bgmHandle);

	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	// ����������T�E���h���폜
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_enemyStartSe);
	DeleteSoundMem(m_hitSe);
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
