#include <DxLib.h>
#include "Enemy7.h"
#include "Game.h"

void InitEnemy(Enemy& enemy)
{
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.x = 0;
	enemy.y = 50;

	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���_���[�W���̏�ԊǗ��p�̕ϐ���������
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
	enemy.isDamage = false;

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(enemy.handle, &enemy.w, &enemy.h);

	// �G�l�~�[���E�ړ����Ă��邩�ǂ����̃t���O�����Z�b�g
	enemy.isRightMove = true;
}

void UpdateEnemy(Enemy& enemy)
{
	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (enemy.isRightMove == true)
	{
		enemy.x += 3;
	}
	else
	{
		enemy.x -= 3;
	}

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (enemy.x > ScreenSizeX - 24)
	{
		enemy.x = ScreenSizeX - 24;
		enemy.isRightMove = false;
	}
	else if (enemy.x < 0)
	{
		enemy.x = 0;
		enemy.isRightMove = true;
	}

	if (enemy.isDamage)
	{

		// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
		enemy.damageCounter++;

		// �������c�ߏ��߂� �R�O �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
		// ���ɖ߂��Ă�����
		if (enemy.damageCounter == 30)
		{
			enemy.isDamage = false;
		}
	}
}

void DrawEnemy(Enemy& enemy)
{
	// �G�l�~�[��`��
			// ���c�߂Ă��邩�ǂ����ŏ����𕪊�
	if (enemy.isDamage)
	{
		// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		DrawGraph(enemy.x, enemy.y, enemy.damageHandle, FALSE);
	}
	else
	{
		DrawGraph(enemy.x, enemy.y, enemy.handle, FALSE);
	}
}
