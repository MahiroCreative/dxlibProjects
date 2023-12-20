#include <DxLib.h>

#include "EnemyLeft.h"

#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	// 上下の移動量
	constexpr float kWaveRange = 32.0f;
	// 振動の速さ
	constexpr float kWaveSpeed = 0.1f;

	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 64;

	constexpr float kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr float kGraphHalfHeight = kGraphHeight / 2.0f;
}

EnemyLeft::EnemyLeft() :
	EnemyBase(),	// 明示的に呼ぶ場合の例
	m_sinRate(0)
{
	// 基底クラスのコンストラクタを明示的に呼ばなくてもここで呼ばれる
}

EnemyLeft::~EnemyLeft()
{
	// デストラクタも呼ばれる　はず…
}

void EnemyLeft::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	m_basePos += m_vec;
	m_pos = m_basePos;

	m_sinRate += kWaveSpeed;
	m_pos.y += sinf(m_sinRate) * kWaveRange;
	

	// 当たり判定の更新
	UpdateCollision();

	if (Game::kScreenWidth + kGraphHalfWidth < m_pos.x) m_isExist = false;
}

void EnemyLeft::Start()
{
	// 画面中央に敵キャラクターを登場させる
	m_isExist = true;

	m_basePos.x = static_cast<float>(0 - kGraphHalfWidth);
	m_basePos.y = static_cast<float>(GetRand(Game::kScreenHeight - kGraphHeight) + kGraphHalfHeight);
	m_pos = m_basePos;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}
