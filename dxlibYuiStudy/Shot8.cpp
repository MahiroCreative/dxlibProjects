#include "Shot8.h"
#include "Enemy8.h"

//----------------------------//
// �V���b�g�֐��Q.
//----------------------------//
// ������.
void Shot::Init()
{
	// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h.
	Graph = LoadGraph("Resources/SuperShot.png");

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	isVisible = false;

	// �e�̃O���t�B�b�N�̃T�C�Y������
	GetGraphSize(Graph, &W, &H);
}

// �A�b�v�f�[�g.
void Shot::Update(Enemy& enemy)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (isVisible == true)
	{
		// �ei���ړ�������
		Y -= SHOT_SPEED;

		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (Y < 0 - H)
		{
			isVisible = false;
		}
	}

	// �e�̂����蔻��.
	// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
	if (isVisible == 1 && enemy.GetLife() > 0)
	{
		// �G�l�~�[�Ƃ̓����蔻��
		if (((X > enemy.GetPosX() && X < enemy.GetPosX() + enemy.GetSizeW()) ||
			(enemy.GetPosX() > X && enemy.GetPosX() < X + W)) &&
			((Y > enemy.GetPosY() && Y < enemy.GetPosY() + enemy.GetSizeH()) ||
				(enemy.GetPosY() > Y && enemy.GetPosY() < Y + H)))
		{
			// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
			isVisible = 0;

			enemy.OnDamage();
		}
	}
}
// �`��.
void Shot::Draw()
{
	if (isVisible == true)
	{
		// ��ʂɒei��`�悷��
		DrawGraph(X, Y, Graph, TRUE);
	}
}

void Shot::OnShoot(int startX, int startY)
{
	// �ei�̈ʒu���Z�b�g�A�ʒu�͒e����������̒��S�ɂ���
	X = startX;
	Y = startY;

	// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
	isVisible = true;
}
