#include <DxLib.h>
#include <cassert>
#include "Game.h"

#include "ShotMagicWand.h"

#include "SceneMain.h"

namespace
{
	// ショットの大きさ
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	constexpr float kHalfWidth = kWidth / 2.0f;
	constexpr float kHalfHeight = kHeight / 2.0f;

	// 弾の移動速度
	constexpr float kShotSpeed = 8.0f;

	// 覚えておく過去の位置情報の数
	constexpr int kPosLogNum = 8;
	constexpr int kPosAlpha = 255 / kPosLogNum;	// 消えていいやつ(自作)
}

ShotMagicWand::ShotMagicWand()
{
	m_posLog.resize(kPosLogNum);
}

ShotMagicWand::~ShotMagicWand()
{
}

void ShotMagicWand::Init()
{
}

void ShotMagicWand::Update()
{
	if (!m_isExist) return;

	// ログの保存処理
	for (int i = m_posLog.size() - 1; i > 0; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);


	// 画面外に出た処理
	// 過去の表示位置も含めてすべて画面外に出たら終了
	bool isOut = false;
	if (m_pos.x < 0.0f - kHalfWidth)				isOut = true;
	if (Game::kScreenWidth + kHalfWidth < m_pos.x)	isOut = true;
	if (m_pos.y <= 0.0f - kHalfHeight)				isOut = true;
	if (Game::kScreenHeight + kHalfHeight < m_pos.y)isOut = true;
	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// 過去ログも画面内にあるかをチェックする
	for (const auto& posLog : m_posLog)
	{
		isOut = false;
		if (posLog.x < 0.0f - kHalfWidth)				isOut = true;
		if (Game::kScreenWidth + kHalfWidth < posLog.x)	isOut = true;
		if (posLog.y <= 0.0f - kHalfHeight)				isOut = true;
		if (Game::kScreenHeight + kHalfHeight < posLog.y)isOut = true;
		// チェック中の座標が画面内ならここで終了
		if (!isOut) return;
	}

	m_isExist = false;
#if false
	if ((m_vec.x < 0.0f) &&
		(m_pos.x <= 0.0f - kHalfWidth))
	{
		m_isExist = false;
	}
	if ((0.0f < m_vec.x) &&
		(Game::kScreenWidth + kHalfWidth < m_pos.x))
	{
		m_isExist = false;
	}
	if ((m_vec.y < 0.0f) &&
		(m_pos.y <= 0.0f - kHalfHeight))
	{
		m_isExist = false;
	}
	if ((0.0f < m_vec.y) &&
		(Game::kScreenHeight + kHalfHeight < m_pos.y))
	{
		m_isExist = false;
	}
#endif
}

void ShotMagicWand::Draw() const
{
	if (!m_isExist) return;
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (const auto& posLog : m_posLog)
	{
		for (int lineNum = 0; lineNum < 8; lineNum++)
		{
			int startX = static_cast<int>(m_pos.x);
			int startY = static_cast<int>(m_pos.y);
			int endX = static_cast<int>(posLog.x);
			int endY = static_cast<int>(posLog.y);

			// ここからはやってない内容(予習内容)
			// かっこよくするためのこと
			float angle = GetRand(359) / 360.f * DX_TWO_PI_F;
			float len = (GetRand(6) - 3) * 1.5f;

			startX += static_cast<int>(cosf(angle) * len);
			startY += static_cast<int>(sinf(angle) * len);
			endX += static_cast<int>(cosf(angle) * len);
			endY += static_cast<int>(sinf(angle) * len);

			DrawLine(startX, startY,
				endX, endY,
				0x010210, static_cast<int>(kWidth) - lineNum);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	m_colRect.Draw(0x000000, false);
#endif
}

void ShotMagicWand::Start(Vec2 pos)
{
	assert(m_pMain);

	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;

	// 過去ログの初期情報を初期化時点では同じ位置にしてしまう
	// 残像が変な位置に表示されないため
	for (auto& posLog : m_posLog)
		posLog = pos;

	assert(m_pMain);

	// 仮実装　右方向に移動させる
	//m_vec.x = kShotSpeed;
	//m_vec.y = 0.0f;
	m_vec = m_pMain->GetNearEnemyPos(m_pos) - m_pos;
	m_vec.Normalize();
	m_vec *= kShotSpeed;
}
