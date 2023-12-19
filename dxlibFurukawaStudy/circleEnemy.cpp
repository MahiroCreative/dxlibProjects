#include "DxLib.h"
#include "circleEnemy.h"
#include <cmath>

// 定数定義
namespace
{
	constexpr int kDefaultPosX = 320;	// 初期X座標
	constexpr int kDefaultPosY = 240;	// 初期Y座標
	constexpr int kRadius = 48;			// 半径
	constexpr int kMaXMoveX = 10;		// X軸の移動速度の最大値
	constexpr int kMaXMoveY = 10;		// Y軸の移動速度の最大値

	const unsigned int kNotHitColor = GetColor(200, 200, 200);	// 当たっていない時の色
	const unsigned int kHitColor = GetColor(200, 0, 0);			// 当たっている時の色

	constexpr int kScreenWeight = 640;
	constexpr int kScreenHeight = 480;

	constexpr int kDelaySpeedTime = 10 * 1000;	// スピードが変わるまでの時間(*1000することでmsに変換)
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
		// 当たっていない
		DrawCircle(m_posX, m_posY, m_radius, kNotHitColor, true);
	}
	else
	{
		// 当たっている
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