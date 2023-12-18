//-----------------------------------------------------------------------------
// @brief  �G�l�~�[����.
//-----------------------------------------------------------------------------

#pragma once

#include "DxLib.h"
#include "Game8.h"

// �G�l�~�[�\����.
class Enemy
{
private:
	int		X;
	int		Y;
	int		Graph;
	bool	DamageFlag;
	int		DamageCounter;
	int		DamageGraph;
	int		W;
	int		H;
	int		Life;

	// �G�l�~�[���E�ړ����Ă��邩�ǂ���
	bool	RightMove;

public:
	// ������.
	void Init();
	// �A�b�v�f�[�g.
	void Update();
	// �`��.
	void Draw();
	void OnDamage();

	// getter
	int GetPosX() const { return X; }
	int GetPosY() const { return Y; }
	int GetSizeW() const { return W; }
	int GetSizeH() const { return H; }
	int GetLife() const { return Life; }
};
