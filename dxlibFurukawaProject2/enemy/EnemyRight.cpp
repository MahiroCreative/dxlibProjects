#include <DxLib.h>

#include "EnemyRight.h"

#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	constexpr float kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr float kGraphHalfHeight = kGraphHeight / 2.0f;
}

EnemyRight::EnemyRight()
{
}

EnemyRight::~EnemyRight()
{
}

void EnemyRight::Update()
{
	// 存在しない敵は処理しない
	if (!m_isExist) return;

	m_pos += m_vec;
	// 当たり判定の更新
	UpdateCollision();

	// ベクトルをいじってみる
	// 画面中央を超えたら加速していく
	if (m_pos.x < Game::kScreenWidth / 2)
	{
		// 移動ベクトルを変化させる事で速度を上げる
		// 左に移動する量を大きくすることで早く動いているように見せる
		m_vec.x -= 0.5f;
	}

	// 画面外に出たら存在を消す
	if (m_pos.x < 0.0f - kGraphHalfWidth)
	{
		m_isExist = false;
	}
}

void EnemyRight::Start()
{
	m_isExist = true;

	m_pos.x = static_cast<float>(Game::kScreenWidth + kGraphHalfWidth);
	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - kGraphHeight) + kGraphHalfHeight);

	// 1フレーム当たりの移動ベクトルを決定する
	m_vec.x = -kSpeed;
}