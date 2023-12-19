#include <DxLib.h>
#include <cassert>
#include "Enemy1.h"

namespace
{
	// 移動速度
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
		m_moveX *= -1;	// 進行方向反転
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

	//ガタガタした動きの作成
	posX += GetRand(5) - 2;
	posY += GetRand(5) - 2;

	if (m_moveX < 0)
	{
		DrawGraph(posX, posY, m_handle, false);
	}
	else
	{
		DrawTurnGraph(posX, posY, m_handle, false);	// 左右反転表示
	}
}

void Enemy::SetHandle(int handle)
{
	m_handle = handle;

	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Enemy::SetStartPos()
{
	// グラフィックのサイズが決定しないと
	// 画面外に決定されるかも！

	// グラフィックを決定する前に呼ばれていたらそれに気づくようにしたい
	// グラフィックが決まる前にここに来たら止まるようにしたい
	// assert(止まらない条件);
	assert(m_handle != -1);

	m_posX = GetRand(640 - m_graphWidth);
	m_posY = GetRand(480 - m_graphHeight);
}