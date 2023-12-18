#pragma once

#include "DxLib.h"
#include "Game8.h"
#include "Enemy8.h"

// �V���b�g.
struct Shot
{
private:
	int		Graph;
	int		X;
	int		Y;
	bool	isVisible;
	int		W;
	int		H;

public:
	// ������.
	void Init();
	// �A�b�v�f�[�g.
	void Update(Enemy& enemy);
	// �`��.
	void Draw();

	// getter
	bool IsVisible() const { return isVisible; }
	int GetSizeW() const { return W; }
	int GetSizeH() const { return H; }

	void OnShoot(int startX, int startY);
};
