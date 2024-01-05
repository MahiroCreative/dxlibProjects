#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "GameObjectBase.h"

class Player : public GameObjectBase
{
private:
	/*�����o�ϐ�*/
	int _drawHandle;//�摜�n���h��
	IntVector _pos;//���W
public:
	/*�R���X�g���N�^*/
	Player()
	{
		_pos = IntVector();
		_drawHandle = LoadGraph("Resources/player.png");
	}
	/*�����o�֐�*/
	void Update() override
	{
		_pos.X += 1;
		_pos.Y += 1;
	}
	void Draw() const override
	{
		DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
	}
	void Sound() const override
	{

	}
};

