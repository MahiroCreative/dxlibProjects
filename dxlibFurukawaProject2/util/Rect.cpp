#include "Rect.h"
#include <DxLib.h>
#include <cassert>

Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill) const
{
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top), static_cast<int>(m_right), static_cast<int>(m_bottom),
		color, isFill);
}

void Rect::SetLT(float left, float top, float width, float height)
{
	m_left = left;
	m_top = top;
	m_right = left + width;
	m_bottom = top + height;
}

void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}

float Rect::GetWidth() const
{
	assert(m_left <= m_right);	// 左右の座標入れ替わりチェック
	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_top <= m_bottom);	// 上下の座標入れ替わりチェック
	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	return Vec2{ (m_left + m_right) / 2, (m_top + m_bottom) / 2 };
}

bool Rect::IsCollsion(const Rect& target)
{
	// 絶対に当たらないパターンをはじいていく
	if (target.m_right < m_left) return false;
	if (target.m_bottom < m_top) return false;
	if (m_right < target.m_left) return false;
	if (m_bottom < target.m_top) return false;

	// 当たらないパターン以外は当たっている
	return true;
}
