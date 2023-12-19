#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "Player2.h"
#include "Enemy.h"

namespace
{
	// 初期位置
	constexpr float kDefaultPosX = Game::kScreenWidht / 2.0f;
	constexpr float kDefaultPosY = Game::kScreenHeight - 100.0f;

	// 移動量
	constexpr float kSpeed = 8.0f;
}

Player::Player() :
	m_handle(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_walkSe(-1),
	m_posX(0.0f),
	m_posY(0.0f),
	m_isTurn(false)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_isTurn = false;
	SetStartPos();
}

void Player::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (pad != 0)
	{
		PlaySoundMem(m_walkSe, DX_PLAYTYPE_BACK, false);
		if (pad & PAD_INPUT_LEFT)
		{
			m_posX -= kSpeed;
			m_isTurn = false;
		}
		if (pad & PAD_INPUT_RIGHT)
		{
			m_posX += kSpeed;
			m_isTurn = true;
		}

		if (m_posX < 0)
		{
			m_posX = 0;
		}
		if (Game::kScreenWidht - m_graphWidth < m_posX)
		{
			m_posX = static_cast<float>(Game::kScreenWidht - m_graphWidth);
		}
	}
	else
	{
		StopSoundMem(m_walkSe);
	}
}

void Player::Draw() const
{
	assert(m_handle != -1);

	if (m_isTurn)
	{
		DrawTurnGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
	}
	else
	{
		DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
	}
}

void Player::SetGraphHandle(int handle)
{
	m_handle = handle;

	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Player::SetStartPos()
{
	m_posX = kDefaultPosX - m_graphWidth / 2;
	m_posY = kDefaultPosY - m_graphHeight / 2;
}

bool Player::IsCollision(const Enemy& enemy)
{
	// 存在しない敵とは当たらない
	if (!enemy.IsExist()) return false;

	if (enemy.GetRight() < m_posX)					return false;	// 敵の右判定よりプレイヤーの左判定が右側にある場合当たっていない
	if (m_posX + m_graphWidth < enemy.GetLeft())	return false;	// プレイヤーの右判定より敵の左判定が右側にある場合当たっていない
	if (enemy.GetDown() < m_posY)					return false;	// 敵の下判定よりプレイヤーの上判定が下側にある場合当たっていない
	if (m_posY + m_graphHeight < enemy.GetUp())		return false;	// プレイヤーの下判定より敵の上判定が下側にある場合当たっていない

	return true;
}