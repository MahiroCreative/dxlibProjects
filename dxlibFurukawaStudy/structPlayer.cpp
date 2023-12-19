#include "DxLib.h"
#include "structPlayer.h"
#include "structEnemy.h"

// �v���C���[�̏�����
void initPlayer(Player* pPlayer, int tempNoHitHandle, int tempHitHandle)
{
	pPlayer->noHitHandle = tempNoHitHandle;
	pPlayer->hitHandle = tempHitHandle;
	pPlayer->x = 320.0f;
	pPlayer->y = 240.0f;
	// ���ꂼ��̓����蔻��̏ꏊ����
	pPlayer->detectionLeft = 0;
	pPlayer->detectionRight = 32;
	pPlayer->detectionUp = 0;
	pPlayer->detectionDown = 32;
}

// �v���C���[��`�悷��֐�
void drawPlayer(Player player, int detection)
{
	// �G�ɂ����������ǂ���
	if (detection == NOT_HIT)
	{
		// �������Ă��Ȃ���Ε���ver.��`��
		DrawGraph((int)player.x, (int)player.y, player.noHitHandle, 0);
	}
	else if (detection == HIT)
	{
		// �������Ă���΁~��ver.��`��
		DrawGraph((int)player.x, (int)player.y, player.hitHandle, 0);
	}
}

// �����蔻��
int CollisionDetection(Player player, Enemy enemy[])
{
	// �S�L�����N�^�[�𔻒� (CHARA_MAX�ł�OK)
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		/// �����蔻����W + ���ݒn
		// ����
		const int playerLeftX = player.detectionLeft + player.x;
		const int playerUpY = player.detectionUp + player.y;
		const int playerRightX = player.detectionRight + player.x;
		const int playerDownY = player.detectionDown + player.y;
		// �G
		const int enemyLeftX = enemy[i].detectionLeft + enemy[i].x;
		const int enemyUpY = enemy[i].detectionUp + enemy[i].y;
		const int enemyRightX = enemy[i].detectionRight + enemy[i].x;
		const int enemyDownY = enemy[i].detectionDown + enemy[i].y;

		/// ����
		// �����&&�ō��E�œ������Ă��Ȃ�������
		// �E���&&�ŏ㉺�œ������Ă��Ȃ�������
		if ((playerLeftX < enemyRightX) && (enemyLeftX < playerRightX) && (playerUpY < enemyDownY) && (enemyUpY < playerDownY))
		{
			return HIT;
		}
	}
	return NOT_HIT;
}

// �v���C���[�̈ړ��֐�
void updatePlayer(Player* pPlayer)
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((padState & PAD_INPUT_UP) != 0)		// ��L�[������Ă���
	{
		pPlayer->y -= 2.5f;
		if (pPlayer->y < 0)	// ��ʊO�ɏo�悤�Ƃ���
		{
			pPlayer->y = 0;
		}
	}
	if ((padState & PAD_INPUT_DOWN) != 0)	// ���L�[������Ă���
	{
		pPlayer->y += 2.5f;
		if (pPlayer->y > 480 - 32)
		{
			pPlayer->y = 480 - 32;
		}
	}
	if ((padState & PAD_INPUT_LEFT) != 0)	// ���L�[������Ă���
	{
		pPlayer->x -= 2.5f;
		if (pPlayer->x < 0)
		{
			pPlayer->x = 0;
		}
	}
	if ((padState & PAD_INPUT_RIGHT) != 0)	// �E�L�[������Ă���
	{
		pPlayer->x += 2.5f;
		if (pPlayer->x > 640 - 32)
		{
			pPlayer->x = 640 - 32;
		}
	}
}