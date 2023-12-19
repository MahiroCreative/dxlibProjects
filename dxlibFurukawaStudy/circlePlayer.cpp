#include "DxLib.h"
#include "circlePlayer.h"
#include "circleEnemy.h"
#include <cmath>

// 定数の宣言
namespace
{
	constexpr int kRadius = 16;
	constexpr int kMaxHp = 10;

	constexpr int kHpBarSize = 20;

	const unsigned int kHitColor = GetColor(150, 150, 150);
	const unsigned int kNotHitColor = GetColor(255, 255, 255);

	constexpr int kDelayTime = 1000;	// 1000msのディレイ時間

	constexpr int kScreenWeight = 640;
	constexpr int kScreenHeight = 480;
}

// 関数の宣言
void DrawHpBar(int hp);

// メンバ関数の実装
Player::Player() :
	m_posX(0),
	m_posY(0),
	m_radius(kRadius),
	m_hp(kMaxHp),
	m_isHit(false)
{

}

Player::~Player()
{

}

void Player::Init()
{
	m_hp = kMaxHp;
	m_isHit = false;
}

void Player::Update()
{
	GetMousePoint(&m_posX, &m_posY);

	if (m_posX < kRadius)					m_posX = kRadius;
	if (kScreenWeight - kRadius < m_posX)	m_posX = kScreenWeight - kRadius;
	if (m_posY < kRadius)					m_posY = kRadius;
	if (kScreenHeight - kRadius < m_posY)	m_posY = kScreenHeight - kRadius;
}

void Player::Draw() const
{
	DrawPlayer();

	DrawHpBar(m_hp);
}

void Player::DrawPlayer() const
{
	DrawCircle(m_posX, m_posY, m_radius, kNotHitColor, true);
	if (m_isHit)
	{
		DrawCircle(m_posX, m_posY, m_radius, kHitColor, true);
	}
}

void Player::Collision(Enemy& enemy, const int kEnemyNum)
{
	static int lastHitTime = GetNowCount();

	if (GetNowCount() - lastHitTime > kDelayTime)
	{
		m_isHit = false;
	}

	for (int i = 0; i < kEnemyNum; i++)
	{
		float dx = (float)(enemy.GetPosX() - m_posX);	// 横軸の距離
		float dy = (float)(enemy.GetPosY() - m_posY);	// 縦軸の距離
		bool col = m_radius + enemy.GetRadius() >= sqrtf(dx * dx + dy * dy);

		// 当たった
		if (col)
		{
			if (!m_isHit)
			{
				lastHitTime = GetNowCount();
				m_isHit = true;
				m_hp--;
			}
			if (enemy.GetIsHit())
			{
				enemy.ChangIsHit();
			}
		}
		// ずれた
		if (!col && !enemy.GetIsHit())
		{
			enemy.ChangIsHit();
		}
	}
}

bool Player::isExist() const
{
	return m_hp > 0;
}

void DrawHpBar(const int hp)
{
	for (int i = 0; i < hp; i++)
	{
		DrawBox(i * kHpBarSize, 0, kHpBarSize + i * kHpBarSize, 20, GetColor(0, 255, 0), true);
	}
	for (int i = hp; i < kMaxHp; i++)
	{
		DrawBox(i * kHpBarSize, 0, kHpBarSize + i * kHpBarSize, 20, GetColor(255, 0, 0), true);
	}
	DrawFormatString(kHpBarSize * 11, 0, GetColor(255, 255, 255), " %d / %d ", hp, kMaxHp);
}