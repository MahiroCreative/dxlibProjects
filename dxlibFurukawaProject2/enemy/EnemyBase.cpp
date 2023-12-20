#include <DxLib.h>
#include <cassert>

#include "EnemyBase.h"

#include "Game.h"

namespace
{
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
}

EnemyBase::EnemyBase() :
	m_handle(-1),
	m_isExist(false)
	// m_posは引数なしのコンストラクタが呼ばれる
	// 引数なしのコンストラクタを呼ぶ場合は省略できる
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	// 存在しない敵は処理しない
	if (!m_isExist) return;
}

void EnemyBase::Draw() const
{
	// 存在しない敵は描画しない
	if (!m_isExist) return;
	// グラフィックが設定されていなければ止まる
	assert(m_handle >= 0);
	// 中心位置を基準として描画する
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, false, false);

#ifdef _DEBUG
	m_colRect.Draw(0xff0000, false);
#endif
}

void EnemyBase::UpdateCollision()
{
	//m_colRect.SetLT(m_pos.x - kGraphWidth / 2, m_pos.y - kGraphHeight / 2, kGraphWidth, kGraphHeight);
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
}
