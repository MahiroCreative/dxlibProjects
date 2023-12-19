#include "DxLib.h"
#include "circleEnemy.h"
#include <cmath>

// �萔��`
namespace
{
	constexpr int kDefaultPosX = 320;	// ����X���W
	constexpr int kDefaultPosY = 240;	// ����Y���W
	constexpr int kRadius = 48;			// ���a
	constexpr int kMaXMoveX = 10;		// X���̈ړ����x�̍ő�l
	constexpr int kMaXMoveY = 10;		// Y���̈ړ����x�̍ő�l

	const unsigned int kNotHitColor = GetColor(200, 200, 200);	// �������Ă��Ȃ����̐F
	const unsigned int kHitColor = GetColor(200, 0, 0);			// �������Ă��鎞�̐F

	constexpr int kScreenWeight = 640;
	constexpr int kScreenHeight = 480;

	constexpr int kDelaySpeedTime = 10 * 1000;	// �X�s�[�h���ς��܂ł̎���(*1000���邱�Ƃ�ms�ɕϊ�)
}

Enemy::Enemy() :
	m_posX(kDefaultPosX),
	m_posY(kDefaultPosY),
	m_radius(kRadius),
	m_isHit(true),
	m_moveX(0),
	m_moveY(0),
	m_changTime(0)
{
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	m_posX = GetRand(kScreenWeight);
	m_posY = GetRand(kScreenHeight);

	m_moveX = GetRand(kMaXMoveX);
	m_moveY = GetRand(kMaXMoveY);

	m_isHit = true;
	m_changTime = GetNowCount();
}

void Enemy::Update()
{
	m_posX += m_moveX;
	m_posY += m_moveY;

	if (m_posX < kRadius)
	{
		m_posX = kRadius;
		m_moveX *= -1;
	}
	if (m_posX > kScreenWeight - kRadius)
	{
		m_posX = kScreenWeight - kRadius;
		m_moveX *= -1;
	}
	if (m_posY < 0 + kRadius)
	{
		m_posY = 0 + kRadius;
		m_moveY *= -1;
	}
	if (m_posY > kScreenHeight - kRadius)
	{
		m_posY = kScreenHeight - kRadius;
		m_moveY *= -1;
	}

	if (GetNowCount() - m_changTime > kDelaySpeedTime)
	{
		if (m_moveX >= 0)	m_moveX = GetRand(kMaXMoveX);
		else				m_moveX = GetRand(kMaXMoveX) * -1;

		if (m_moveY >= 0)	m_moveY = GetRand(kMaXMoveY);
		else				m_moveY = GetRand(kMaXMoveY) * -1;

		m_changTime = GetNowCount();
	}
}

void Enemy::Draw()
{
	if (m_isHit)
	{
		// �������Ă��Ȃ�
		DrawCircle(m_posX, m_posY, m_radius, kNotHitColor, true);
	}
	else
	{
		// �������Ă���
		DrawCircle(m_posX, m_posY, m_radius, kHitColor, true);
	}
}

void Enemy::SetPosX(int x)
{
	m_posX = x;

	if (m_posX < 0)
	{
		m_posX = 0;
	}
	if (m_posX > kScreenWeight)
	{
		m_posX = kScreenWeight;
	}
}

int Enemy::GetDelayChangTime() const
{
	return kDelaySpeedTime;
}