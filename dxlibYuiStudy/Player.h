#pragma once
#include "Game.h"

struct Shot;

// �\���̐錾
struct Player
{
	int handle = -1;
	Position pos;
	Size size;

	bool isPrevshot = false;
};

// �v���g�^�C�v�錾
void InitializePlayer(Player& player);// �v���C���[�̏���������
void UpdatePlayer(Player& player, Shot shot[], int shotNum);// �v���C���[�̍X�V
void DrawPlayer(Player& player);