#include <DxLib.h>
#include <cassert>
#include "Enemy1.h"

namespace
{
	// �ړ����x
	constexpr int kMoveSpeed = 4;
}

Enemy::Enemy() :
	m_handle(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_posX(0),
	m_posY(0),
	m_moveX(kMoveSpeed)
{
	if (GetRand(1))
	{
		m_moveX *= -1;
	}
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{

}

void Enemy::Update()
{
	m_posX += m_moveX;
	if (m_posX < 0)
	{
		m_posX = 0;
		m_moveX *= -1;	// �i�s�������]
	}
	if (m_posX > 640 - m_graphWidth)
	{
		m_posX = 640 - m_graphWidth;
		m_moveX *= -1;
	}

}

void Enemy::Draw() const
{
	int posX = m_posX;
	int posY = m_posY;

	//�K�^�K�^���������̍쐬
	posX += GetRand(5) - 2;
	posY += GetRand(5) - 2;

	if (m_moveX < 0)
	{
		DrawGraph(posX, posY, m_handle, false);
	}
	else
	{
		DrawTurnGraph(posX, posY, m_handle, false);	// ���E���]�\��
	}
}

void Enemy::SetHandle(int handle)
{
	m_handle = handle;

	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Enemy::SetStartPos()
{
	// �O���t�B�b�N�̃T�C�Y�����肵�Ȃ���
	// ��ʊO�Ɍ��肳��邩���I

	// �O���t�B�b�N�����肷��O�ɌĂ΂�Ă����炻��ɋC�Â��悤�ɂ�����
	// �O���t�B�b�N�����܂�O�ɂ����ɗ�����~�܂�悤�ɂ�����
	// assert(�~�܂�Ȃ�����);
	assert(m_handle != -1);

	m_posX = GetRand(640 - m_graphWidth);
	m_posY = GetRand(480 - m_graphHeight);
}