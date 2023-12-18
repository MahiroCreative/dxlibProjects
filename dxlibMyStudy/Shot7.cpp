#include <DxLib.h>
#include "Shot7.h"
#include "Enemy7.h"
#include "Game.h"

void InitShot(Shot& shot, int handle, int sizeW, int sizeH)
{
	shot.handle = handle;
	shot.isShot = false;
	shot.w = sizeW;
	shot.h = sizeH;
}

void UpdateShot(Shot& shot, Enemy& enemy)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (shot.isShot == true)
	{
		// �ei���P�U�h�b�g��Ɉړ�������
		shot.y -= 16;

		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (shot.y < -80)
		{
			shot.isShot = false;
		}
	}

	// �e�̂����蔻��.
	// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
	if (shot.isShot)
	{
		// �G�l�~�[�Ƃ̓����蔻��
		if (((shot.x > enemy.x && shot.x < enemy.x + enemy.w) ||
			(enemy.x > shot.x && enemy.x < shot.x + shot.w)) &&
			((shot.y > enemy.y && shot.y < enemy.y + enemy.h) ||
				(enemy.y > shot.y && enemy.y < shot.y + shot.h)))
		{
			// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
			shot.isShot = false;

			// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
			enemy.isDamage = true;

			// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
			enemy.damageCounter = 0;
		}
	}
}

void DrawShot(Shot& shot)
{
	if (!shot.isShot) return;

	// ��ʂɒei��`�悷��
	DrawGraph(shot.x, shot.y, shot.handle, FALSE);
}
