#include <DxLib.h>
#include <cassert>
#include "SceneMain2.h"
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

SceneMain::SceneMain()
//	m_playerHandle(-1),
//	m_enemyHandle(-1),
//	m_bgHandle(-1),
//	m_bgmHandle(-1),
//	m_enemyStartSe(-1),
//	m_hitSe(-1),
//	m_walkSe(-1),
//	m_player(),
//	m_enemy(),
//	m_isGameOver(false),
//	m_isSceneEnd(false),
//	m_playFrameCount(0),
//	m_enemyCreateNum(0),
//	m_enemyWaitFrame(0),
//	m_fadeAlpha(255)			// �s�����ŏ�����
{
}

SceneMain::~SceneMain()
{
}