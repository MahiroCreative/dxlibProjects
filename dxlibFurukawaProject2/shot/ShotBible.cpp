#include <DxLib.h>
#include <cassert>
#include <cmath>

#include "ShotBible.h"

#include "Player.h"

namespace
{
	// �e�̑傫��
	constexpr int kWidth = 16;
	constexpr int kHeight = 24;
	constexpr int kHalfWidth = kWidth / 2;
	constexpr int kHalfHeight = kHeight / 2;

	// �������Ă��������܂ł̃t���[����
	constexpr int kExistFrame = 60 * 5;
	// �v���C���[�̎����1��]����̂ɂ�����t���[����
	constexpr int kRotFrame = 60;

	// �v���C���[�̎�������Ƃ��̔��a
	constexpr float kRadius = 100.0f;

	// �v���C���[���猩�����Έʒu���f�[�^�Ƃ��Ď���
	const Vec2 kOffset[] = 
	{
		Vec2{kRadius, 0.0f},	// �E
		Vec2{0.0f, kRadius},	// ��
		Vec2{-kRadius, 0.0f},	// ��
		Vec2{0.0f, -kRadius},	// ��
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
	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��������~
	assert(m_pPlayer);

	// ��莞�Ԃ����������
	m_frameCount++;
	if (kExistFrame <= m_frameCount)
	{
		m_isExist = false;
		return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	}

	// �ړ�����
	// �v���C���[�̈ʒu�ɂ���ĕ\������ꏊ���ς��
	// �v���C���[�̈ʒu��񂪗~�����I
	
	/*
	// ������܂ł̐i�s�x�������ϊ�
	float progress = static_cast<float>(m_frameCount) / static_cast<float>(kExistFrame);
	int index = progress * _countof(kOffset);
	*/

	// m_pPlayer->GetPos()	: ��]�̒��S�ʒu
	// m_pos	: �V���b�g�̈ʒu
	// m_angle	: �^�E��0�Ƃ����ꍇ�̉�]�p�x
	// kRadius	: ��]���a

	// �v���C���[���猩���p�x�̍X�V
	m_angle += DX_TWO_PI_F / kRotFrame;

	Vec2 offset;	// �v���C���[���猩���ʒu
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
