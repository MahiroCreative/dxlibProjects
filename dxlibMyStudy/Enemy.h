#pragma once
#include "Game.h"

struct Enemy
{
	//�摜
	int handle = -1;
	int damageHandle = -1;
	//�p�����[�^
	Position pos;
	Size size;
	//�t���O
	bool isDamage = false;
	int damageCount = 0;
	bool isRightMove = true;
};

void InitializeEnemy(Enemy& enemy);// �G�l�~�[�̏���������
void UpdateEnemy(Enemy& enemy);// �G�l�~�[�̍X�V����
void DrawEnemy(Enemy& enemy);// �G�l�~�[�̕`�揈��