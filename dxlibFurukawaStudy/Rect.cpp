#include <DxLib.h>
#include "Rect.h"

namespace
{
	// ランダムに生成する矩形のサイズ制限
	constexpr int kWidthMin = 32;	// 最小幅
	constexpr int kWidthMax = 128;	// 最大幅

	constexpr int kHeightMin = 24;	// 最小高さ
	constexpr int kHeightMax = 96;	// 最大高さ
}

Rect::Rect() :
	m_posX(320),
	m_posY(240),
	m_width(32),
	m_height(32),
	m_color(GetColor(255, 255, 255)),
	m_isFill(false),
	m_isMouseTrase(false)
{
}

Rect::~Rect()
{
}

void Rect::Init()
{
}

void Rect::Update()
{
	// マウス追従フラグがtrueならマウスポインタの位置に移動
	if (m_isMouseTrase)
	{
		GetMousePoint(&m_posX, &m_posY);
	}
}

void Rect::Draw() const
{
	DrawBox(GetLeft(), GetTop(),		// 左上の座標
		GetRight(), GetBottom(),	// 右下の座標
		m_color, m_isFill);
}

void Rect::SetRandom()
{
	m_posX = GetRand(640);
	m_posY = GetRand(480);

	m_width = GetRand(kWidthMax - kWidthMin) + kWidthMin;
	m_height = GetRand(kHeightMax - kHeightMin) + kHeightMin;
}

bool Rect::IsCollision(const Rect& target) const
{
	if (GetLeft() > target.GetRight()) return false;	// 自身の左端の座標より　対象の右端の座標が　左にある場合当たっていない
	if (GetBottom() < target.GetTop()) return false;	// 　　　下　の座標より　　　　上　の座標が　下
	if (GetRight() < target.GetLeft()) return false;	// 　　　右端の座標より　　　　左端の座標が　右
	if (GetTop() > target.GetBottom()) return false;	// 　　　上　の座標より　　　　下　の座標が　上

	// 完全に当たっていないパターンを取り除いて
	// 残った奴は当たっている
	return true;
}
