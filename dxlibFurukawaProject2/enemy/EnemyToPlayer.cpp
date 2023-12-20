#include <DxLib.h>
#include <cassert>

#include "EnemyToPlayer.h"
#include "Player.h"

#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	// キャラクターのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	constexpr float kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr float kGraphHalfHeight = kGraphHeight / 2.0f;
}

EnemyToPlayer::EnemyToPlayer() :
	m_pPlayer(nullptr)
{
	// m_pPlayerにはSceneMainで既にメモリを確保したPlayerが
	// どこに置かれているのか、の情報を入れておきたいのでここではメモリ確保しない
}

EnemyToPlayer::~EnemyToPlayer()
{
	// m_pPlayerの確保解放はSceneMainが管理するので
	// 同様に解放も行わない
}

void EnemyToPlayer::Update()
{
	// 存在しない敵は処理しない
	if (!m_isExist) return;

	m_pos += m_vec;
	// 当たり判定の更新
	UpdateCollision();

	// 画面外に出たら存在を消す
	if ((m_vec.x < 0.0f) &&
		(m_pos.x <= 0.0f - kGraphHalfWidth))
	{
		m_isExist = false;
	}
	if ((0.0f < m_vec.x) &&
		(Game::kScreenWidth + kGraphHalfWidth < m_pos.x))
	{
		m_isExist = false;
	}
	if ((m_vec.y < 0.0f) &&
		(m_pos.y <= 0.0f - kGraphHalfHeight))
	{
		m_isExist = false;
	}
	if ((0.0f < m_vec.y) && 
		(Game::kScreenHeight + kGraphHalfHeight < m_pos.y))
	{
		m_isExist = false;
	}
}

void EnemyToPlayer::Start()
{
	m_isExist = true;
	
	// 画面の上下左右いずれかから登場する
	switch (GetRand(3))
	{
	case 0:	// 上から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - kGraphWidth) + kGraphHalfWidth);
		m_pos.y = static_cast<float>(0 - kGraphHalfHeight);
		break;
	case 1:	// 左から
		m_pos.x = static_cast<float>(0 - kGraphHalfWidth);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - kGraphHeight) + kGraphHalfHeight);
		break;
	case 2:	// 下から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - kGraphWidth) + kGraphHalfWidth);
		m_pos.y = static_cast<float>(Game::kScreenHeight + kGraphHalfHeight);
		break;
	case 3:	// 右から
		m_pos.x = static_cast<float>(Game::kScreenWidth + kGraphHalfWidth);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - kGraphHeight) + kGraphHalfHeight);
		break;
	default:
		assert(false);
		break;
	}

	assert(m_pPlayer);
	// 敵の初期位置からターゲット位置に向かうベクトルを生成
	m_vec = m_pPlayer->GetPos() - m_pos;
	// 正規化(ベクトルの大きさがバラバラなため)
	m_vec.Normalize();
	// ベクトルの長さをスピードに
	m_vec *= kSpeed;
}