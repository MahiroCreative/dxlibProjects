#pragma once
#include "GameCommon.h"

class Player
{
public:
	/*�R���X�g���N�^*/
	Player();
	/*�����o�֐�*/
	void Update();
	void Draw();
	void Sound();
private:
	/*�����o�ϐ�*/
	int _drawHandle;//�摜�n���h��
	IntVector _pos;//���W
};

