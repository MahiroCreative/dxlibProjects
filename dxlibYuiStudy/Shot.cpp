#include "DxLib.h"
#include "Enemy.h"
#include "Shot.h"

// �V���b�g�̏���������
void InitializeShot(Shot& shot, int handle, int sizeW, int sizeH)
{
	// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h.
	shot.handle = handle;
	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	shot.isExist = false;
	// �e�̃O���t�B�b�N�̃T�C�Y������
	shot.size.w = sizeW;
	shot.size.h = sizeH;
}

// �e�̍X�V����
void UpdateShot(Shot& shot, Enemy& enemy)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (shot.isExist == true)
	{
		// �ei���P�U�h�b�g��Ɉړ�������
		shot.pos.y -= ShotSpped;

		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (shot.pos.y < 0 - shot.size.h)
		{
			shot.isExist = false;
		}
	}

	// �e�̂����蔻��.
	// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
	if (shot.isExist == 1)
	{
		// �G�l�~�[�Ƃ̓����蔻��
		if (((shot.pos.x > enemy.pos.x && shot.pos.x < enemy.pos.x + enemy.size.w) ||
			(enemy.pos.x > shot.pos.x && enemy.pos.x < shot.pos.x + shot.size.w)) &&
			((shot.pos.y > enemy.pos.y && shot.pos.y < enemy.pos.y + enemy.size.h) ||
				(enemy.pos.y > shot.pos.y && enemy.pos.y < shot.pos.y + shot.size.h)))
		{
			// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
			shot.isExist = 0;

			// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
			enemy.isDamage = true;

			// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
			enemy.damageCount = 0;
		}
	}
}

// �e�̕`�揈��
void DrawShot(Shot& shot)
{
	if (shot.isExist)
	{
		// ��ʂɒei��`�悷��
		DrawGraph(shot.pos.x, shot.pos.y, shot.handle, FALSE);
	}
}
