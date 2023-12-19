#include "DxLib.h"
#include "structEnemy.h"
#include "structPlayer.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(1);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// �摜����ǂݎ��
	int tempNoHitPlayreHandle = LoadGraph("data/noHitPlayer.png");
	int tempHitPlayerHandle = LoadGraph("data/hitPlayer.png");
	int tempEnemyHandle = LoadGraph("data/enemy.png");

	// �v���C���[�֘A�̏��
	Player player;

	// �v���C���[�̏�����
	initPlayer(&player, tempNoHitPlayreHandle, tempHitPlayerHandle);

	// �G�֘A�̏��
	Enemy enemy[ENEMY_NUM];

	// �G�̏�����
	initAllEnmey(enemy, tempEnemyHandle);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// update
		updatePlayer(&player);

		// �G��update
		updateAllEnemy(enemy);

		// �v���C���[�̕`��
		drawPlayer(player, CollisionDetection(player, enemy));

		// �G�̕`��
		drawAllEnemy(enemy);

		// �����t���R���p�C���𗘗p����
		// Debug�łł̂ݎ��s����鏈������������
#ifdef _DEBUG
		// �v���C���[�̍��W�\��
		DrawFormatString(8, 8, GetColor(2255, 255, 255), "Player(%f, %f)", player.x, player.y);
#endif	// _DEBUG

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();
	}

	DeleteGraph(tempNoHitPlayreHandle);
	DeleteGraph(tempHitPlayerHandle);
	DeleteGraph(tempEnemyHandle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}