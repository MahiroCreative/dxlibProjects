#pragma once

// �V���b�g�̐�.
#define SHOT 20

struct Enemy;

struct Shot
{
	//�摜
	int handle = -1;
	//�p�����[�^
	Position pos;
	Size size;
	//�t���O
	bool isExist = false;
};

void InitializeShot(Shot& shot, int handle, int sizeW, int sizeH);// �V���b�g�̏���������
void UpdateShot(Shot& shot, Enemy& enemy);// �e�̍X�V����
void DrawShot(Shot& shot);// �e�̕`�揈��