#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "Enemy.h"

Enemy::Enemy() :
	m_handle(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_isExist(false),
	m_posX(),
	m_posY(),
	m_moveY(0.0f)
{
	for (int i = 0; i < kPosLogFrame; i++)
	{
		m_posX[i] = 0.0f;
		m_posY[i] = 0.0f;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_isExist = false;
}

void Enemy::Update()
{
	// ���݂��Ȃ��G�̏����͍s��Ȃ�
	if (!m_isExist)	return;

	// �ߋ����O��������炵�Ă���
	for (int i = kPosLogFrame - 1; 1 <= i; i--)
	{
		m_posX[i] = m_posX[i - 1];
		m_posY[i] = m_posY[i - 1];
	}

	m_posY[0] += m_moveY;
	m_moveY += 1.0f;	// ���x�����񂾂񑁂�����

	if (Game::kScreenHeight < m_posY[0])
	{
		// �ʒu�̏�����
	//	SetStartPos();

		// ��ʊO�ɏo�������
		m_isExist = false;
	}
}

void Enemy::Draw() const
{
	// ���݂��Ȃ��G�̕`��͍s��Ȃ�
	if (!m_isExist)	return;

	// �����ɗ�������m_handle��-1���ƃO���t�B�b�N�͐�΂ɕ\������Ȃ�(�o�O)
	assert(m_handle != -1);

	for (int i = kPosLogFrame - 1; 0 <= i; i--)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - i * (255 / kPosLogFrame));
		DrawGraph(static_cast<int>(m_posX[i]), static_cast<int>(m_posY[i]), m_handle, false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	// �ʏ�`��ɖ߂�
}

void Enemy::SetGraphHandle(int handle)
{
	m_handle = handle;

	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Enemy::Start()
{
	m_isExist = true;
	SetStartPos();	// �����_���ȏ����ʒu�ɐݒ�
	m_moveY = 0.0f;	// �������x��������
}

void Enemy::SetStartPos()
{
	assert(m_handle != -1);
	m_posX[0] = static_cast<float>(GetRand(Game::kScreenWidht - m_graphWidth));
	m_posY[0] = static_cast<float>(0 - m_graphHeight);

	for (int i = 1; i < kPosLogFrame; i++)
	{
		m_posX[i] = m_posX[0];
		m_posY[i] = m_posY[0];
	}
}