#pragma once

#define ENEMY_NUM	5

typedef struct Enemy
{
	int handle;				// �G���
	float x;				// ���݂�X���W
	float y;				// ���݂�Y���W
	float moveX;			// X���̈ړ����x
	float moveY;			// Y���̈ړ����x
	float detectionLeft;	// �����蔻�荶��
	float detectionRight;	// �����蔻��E��
	float detectionUp;		// �����蔻��㑤
	float detectionDown;	// �����蔻�艺��
}Enemy;

// �G�̏�����
void initEnemy(Enemy* pEnemy, int tempHandle);

// �S�Ă̓G�̏�����
void initAllEnmey(Enemy* pEnemy, int tempHandle);

// �G�̈ړ��֐�
void updateEnemy(Enemy* pEnemy);

// �S�Ă̓G�̈ړ��֐�
void updateAllEnemy(Enemy* pEnemy);

// �G��\������֐�
void drawEnemy(Enemy enemy);

// �S�Ă̓G��`�悷��֐�
void drawAllEnemy(Enemy enemy[]);