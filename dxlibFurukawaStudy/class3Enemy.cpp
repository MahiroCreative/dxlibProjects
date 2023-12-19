#include "DxLib.h"
#include "class3Enemy.h"
// �R���X�g���N�^
Enemy::Enemy() :
	m_handle(LoadGraph("data/obj.png")),
	m_posX(320),
	m_posY(240)
{

}

// �f�X�g���N�^
Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{

}

void Enemy::Draw()
{
	DrawGraph(m_posX, m_posY, m_handle, false);
}

void Enemy::SetPos(int x, int y)
{
	// ��ʊO�ɏo�Ă�����߂�����
	if (x < 0)			x = 0;
	if (x > 640 - 32)	x = 640 - 32;
	if (y < 0)			y = 0;
	if (y > 480 - 32)	y = 480 - 32;

	m_posX = x;
	m_posY = y;
}