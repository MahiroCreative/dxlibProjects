#pragma once

#include "DxLib.h"
#include "Game8.h"
#include "Shot8.h"

// �v���C���[.
struct Player
{
private:
	int Graph;
	int X;
	int Y;
	int W;
	int H;

	// �V���b�g�̃C���^�[�o����ݒ肷��J�E���^�[
	int shotIntervalCount;

public:
	// ������.
	void Init();
	// �A�b�v�f�[�g.
	void Update(Shot shot[], int shotNum);
	// �`��.
	void Draw();
};
