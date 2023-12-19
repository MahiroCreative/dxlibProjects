#include "DxLib.h"
#include "structEnemy.h"

// �G�̏�����
void initEnemy(Enemy* pEnemy, int tempHandle)
{
	pEnemy->handle = tempHandle;
	pEnemy->x = (float)(GetRand(640 - 32));
	pEnemy->y = (float)(GetRand(480 - 32));
	pEnemy->moveX = 2.5f;
	if (GetRand(1))	pEnemy->moveX *= -1.0f;
	pEnemy->moveY = 2.5f;
	if (GetRand(1))	pEnemy->moveY *= -1.0f;
	pEnemy->detectionLeft = 0;
	pEnemy->detectionRight = 32;
	pEnemy->detectionUp = 0;
	pEnemy->detectionDown = 32;
}

// �S�Ă̓G�̏�����
void initAllEnmey(Enemy* pEnemy, int tempHandle)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		initEnemy(pEnemy + i, tempHandle);
	}
}

// �G�̈ړ��֐�
void updateEnemy(Enemy* pEnemy)
{
	pEnemy->x += pEnemy->moveX;
	pEnemy->y += pEnemy->moveY;
	if (pEnemy->x < 0)
	{
		pEnemy->x = 0;
		pEnemy->moveX *= -1.0f;
	}
	if (pEnemy->x > 640 - 32)
	{
		pEnemy->x = 640 - 32;
		pEnemy->moveX *= -1.0f;
	}
	if (pEnemy->y < 0)
	{
		pEnemy->y = 0;
		pEnemy->moveY *= -1.0f;
	}
	if (pEnemy->y > 480 - 32)
	{
		pEnemy->y = 480 - 32;
		pEnemy->moveY *= -1.0f;
	}
}

// �S�Ă̓G�̈ړ��֐�
void updateAllEnemy(Enemy* pEnemy)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		updateEnemy(pEnemy + i);
	}
}

// �G��`�悷��֐�
void drawEnemy(Enemy enemy)
{
	DrawGraph((int)enemy.x, (int)enemy.y, enemy.handle, 0);
}

// �S�Ă̓G��`�悷��֐�
void drawAllEnemy(Enemy enemy[])
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		drawEnemy(enemy[i]);
	}
}