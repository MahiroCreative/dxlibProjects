#include <DxLib.h>

#include "EnemyLeft.h"

#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	// �㉺�̈ړ���
	constexpr float kWaveRange = 32.0f;
	// �U���̑���
	constexpr float kWaveSpeed = 0.1f;

	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 64;

	constexpr float kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr float kGraphHalfHeight = kGraphHeight / 2.0f;
}

EnemyLeft::EnemyLeft() :
	EnemyBase(),	// �����I�ɌĂԏꍇ�̗�
	m_sinRate(0)
{
	// ���N���X�̃R���X�g���N�^�𖾎��I�ɌĂ΂Ȃ��Ă������ŌĂ΂��
}

EnemyLeft::~EnemyLeft()
{
	// �f�X�g���N�^���Ă΂��@�͂��c
}

void EnemyLeft::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	m_basePos += m_vec;
	m_pos = m_basePos;

	m_sinRate += kWaveSpeed;
	m_pos.y += sinf(m_sinRate) * kWaveRange;
	

	// �����蔻��̍X�V
	UpdateCollision();

	if (Game::kScreenWidth + kGraphHalfWidth < m_pos.x) m_isExist = false;
}

void EnemyLeft::Start()
{
	// ��ʒ����ɓG�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_basePos.x = static_cast<float>(0 - kGraphHalfWidth);
	m_basePos.y = static_cast<float>(GetRand(Game::kScreenHeight - kGraphHeight) + kGraphHalfHeight);
	m_pos = m_basePos;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}
