#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "GameCommon.h"

class Player
{
public:
	/*�R���X�g���N�^*/
	Player()
	{
		_pos = IntVector();
		_drawHandle = LoadGraph("Resources/player.png");
	}
	/*�����o�֐�*/
	void Update()
	{
		_pos.X += 1;
		_pos.Y += 1;
	}
	void Draw()
	{
		DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
	}
	void Sound(){}
private:
	/*�����o�ϐ�*/
	int _drawHandle;//�摜�n���h��
	IntVector _pos;//���W
};

