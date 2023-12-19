#include <DxLib.h>
#include "Rect.h"

namespace
{
	// �����_���ɐ��������`�̃T�C�Y����
	constexpr int kWidthMin = 32;	// �ŏ���
	constexpr int kWidthMax = 128;	// �ő啝

	constexpr int kHeightMin = 24;	// �ŏ�����
	constexpr int kHeightMax = 96;	// �ő卂��
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
	// �}�E�X�Ǐ]�t���O��true�Ȃ�}�E�X�|�C���^�̈ʒu�Ɉړ�
	if (m_isMouseTrase)
	{
		GetMousePoint(&m_posX, &m_posY);
	}
}

void Rect::Draw() const
{
	DrawBox(GetLeft(), GetTop(),		// ����̍��W
		GetRight(), GetBottom(),	// �E���̍��W
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
	if (GetLeft() > target.GetRight()) return false;	// ���g�̍��[�̍��W���@�Ώۂ̉E�[�̍��W���@���ɂ���ꍇ�������Ă��Ȃ�
	if (GetBottom() < target.GetTop()) return false;	// �@�@�@���@�̍��W���@�@�@�@��@�̍��W���@��
	if (GetRight() < target.GetLeft()) return false;	// �@�@�@�E�[�̍��W���@�@�@�@���[�̍��W���@�E
	if (GetTop() > target.GetBottom()) return false;	// �@�@�@��@�̍��W���@�@�@�@���@�̍��W���@��

	// ���S�ɓ������Ă��Ȃ��p�^�[������菜����
	// �c�����z�͓������Ă���
	return true;
}
