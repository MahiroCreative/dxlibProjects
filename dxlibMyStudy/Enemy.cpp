#include "DxLib.h"
#include "Enemy.h"

// �G�l�~�[�̏���������
void InitializeEnemy(Enemy& enemy)
{
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.pos.x = 0;
	enemy.pos.y = 50;

	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���_���[�W���̏�ԊǗ��p�̕ϐ���������
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�	
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
	enemy.isDamage = false;
	enemy.damageCount = 0;

	// �G�l�~�[���E�ړ����Ă��邩�ǂ����̃t���O�����Z�b�g
	enemy.isRightMove = true;
}

// �G�l�~�[�̍X�V����
void UpdateEnemy(Enemy& enemy)
{
	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (enemy.isRightMove == true)
	{
		enemy.pos.x += 3;
	}
	else
	{
		enemy.pos.x -= 3;
	}

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (enemy.pos.x > ScreenSizeX - enemy.size.w)
	{
		enemy.pos.x = ScreenSizeX - enemy.size.w;
		enemy.isRightMove = false;
	}
	else if (enemy.pos.x < 0)
	{
		enemy.pos.x = 0;
		enemy.isRightMove = true;
	}
}

// �G�l�~�[�̕`�揈��
void DrawEnemy(Enemy& enemy)
{
	// �G�l�~�[��`��
	// ���c�߂Ă��邩�ǂ����ŏ����𕪊�
	if (enemy.isDamage == true)
	{
		// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		DrawGraph(enemy.pos.x, enemy.pos.y, enemy.damageHandle, FALSE);

		// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
		enemy.damageCount++;

		// �������c�ߏ��߂� �R�O �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
		// ���ɖ߂��Ă�����
		if (enemy.damageCount == 30)
		{
			// �w�c��ł��Ȃ��x��\���O����
			enemy.isDamage = 0;
		}
	}
	else
	{
		DrawGraph(enemy.pos.x, enemy.pos.y, enemy.handle, FALSE);
	}
}