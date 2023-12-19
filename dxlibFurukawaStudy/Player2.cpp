#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "Player2.h"
#include "Enemy.h"

namespace
{
	// �����ʒu
	constexpr float kDefaultPosX = Game::kScreenWidht / 2.0f;
	constexpr float kDefaultPosY = Game::kScreenHeight - 100.0f;

	// �ړ���
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
	// ���݂��Ȃ��G�Ƃ͓�����Ȃ�
	if (!enemy.IsExist()) return false;

	if (enemy.GetRight() < m_posX)					return false;	// �G�̉E������v���C���[�̍����肪�E���ɂ���ꍇ�������Ă��Ȃ�
	if (m_posX + m_graphWidth < enemy.GetLeft())	return false;	// �v���C���[�̉E������G�̍����肪�E���ɂ���ꍇ�������Ă��Ȃ�
	if (enemy.GetDown() < m_posY)					return false;	// �G�̉�������v���C���[�̏㔻�肪�����ɂ���ꍇ�������Ă��Ȃ�
	if (m_posY + m_graphHeight < enemy.GetUp())		return false;	// �v���C���[�̉�������G�̏㔻�肪�����ɂ���ꍇ�������Ă��Ȃ�

	return true;
}