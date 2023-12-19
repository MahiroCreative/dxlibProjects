#pragma once

#include "structEnemy.h"

#define HIT 1
#define NOT_HIT 0

typedef struct Player
{
	int noHitHandle;				// �������Ă��Ȃ����̉摜��������
	int hitHandle;				// �������Ă��鎞�̉摜��������
	float x;				// ���݂�X���W
	float y;				// ���݂�Y���W
	float detectionLeft;	// �����蔻�荶��
	float detectionRight;	// �����蔻��E��
	float detectionUp;		// �����蔻��㑤
	float detectionDown;	// �����蔻�艺��
}Player;

// �v���C���[�̏�����
void initPlayer(Player* pPlayer, int noHitHandle, int hitHandle);

// �v���C���[��`�悷��֐�(�������ɓ������Ă��邩�̔���)
void drawPlayer(Player player, int detection);

// �����蔻��
int CollisionDetection(Player player, Enemy enemy[]);

// �v���C���[�̈ړ��֐�
void updatePlayer(Player* pPlayer);