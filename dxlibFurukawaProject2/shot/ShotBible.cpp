#include <DxLib.h>
#include <cassert>
#include <cmath>

#include "ShotBible.h"

#include "Player.h"

namespace
{
	// 弾の大きさ
	constexpr int kWidth = 16;
	constexpr int kHeight = 24;
	constexpr int kHalfWidth = kWidth / 2;
	constexpr int kHalfHeight = kHeight / 2;

	// 発生してから消えるまでのフレーム数
	constexpr int kExistFrame = 60 * 5;
	// プレイヤーの周りを1回転するのにかかるフレーム数
	constexpr int kRotFrame = 60;

	// プレイヤーの周りを回るときの半径
	constexpr float kRadius = 100.0f;

	// プレイヤーから見た相対位置をデータとして持つ
	const Vec2 kOffset[] = 
	{
		Vec2{kRadius, 0.0f},	// 右
		Vec2{0.0f, kRadius},	// 下
		Vec2{-kRadius, 0.0f},	// 左
		Vec2{0.0f, -kRadius},	// 上
	};
}

ShotBible::ShotBible() :
	m_frameCount(0),
	m_angle(0)
{
}

ShotBible::~ShotBible()
{
}

void ShotBible::Init()
{
}

void ShotBible::Update()
{
	if (!m_isExist) return;
	// プレイヤーのポインタが設定されていなかったら停止
	assert(m_pPlayer);

	// 一定時間したら消える
	m_frameCount++;
	if (kExistFrame <= m_frameCount)
	{
		m_isExist = false;
		return;	// 終了が確定したら以降の処理は行わない
	}

	// 移動処理
	// プレイヤーの位置によって表示する場所が変わる
	// プレイヤーの位置情報が欲しい！
	
	/*
	// 消えるまでの進行度を割合変換
	float progress = static_cast<float>(m_frameCount) / static_cast<float>(kExistFrame);
	int index = progress * _countof(kOffset);
	*/

	// m_pPlayer->GetPos()	: 回転の中心位置
	// m_pos	: ショットの位置
	// m_angle	: 真右を0とした場合の回転角度
	// kRadius	: 回転半径

	// プレイヤーから見た角度の更新
	m_angle += DX_TWO_PI_F / kRotFrame;

	Vec2 offset;	// プレイヤーから見た位置
	offset.x = cosf(m_angle) * kRadius;
	offset.y = sinf(m_angle) * kRadius;

	m_pos = m_pPlayer->GetPos() + offset;

	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void ShotBible::Draw() const
{
	if (!m_isExist) return;
	
	DrawBox(static_cast<int>(m_pos.x) - kHalfWidth, static_cast<int>(m_pos.y) - kHalfHeight,
		static_cast<int>(m_pos.x) + kHalfWidth, static_cast<int>(m_pos.y) + kHalfHeight,
		0x2020ff, true);
}

void ShotBible::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;
	m_frameCount = 0;

	assert(m_pMain);
}
