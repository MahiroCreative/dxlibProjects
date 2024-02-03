#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//�������A���̃V���[�Y�ŉ��������e�͕K�v�K�v�A�Ƃ������x���ł��B�������o�܂��B
//�܂��A���w�Ҍ����̉���̂悤�Ȏ��͂��Ă��܂���B�g�����̗Ⴊ�����Ă�����x�ł��B
//������Ȃ������͎���\���I�ɒ��ׂĉ������B
//Dxlib�̃��t�@�����X��p�ɂɌ��Ċ֐��ɈӖ��Ȃǂ��m�F���Ȃ���i�߂�̂��������g�����ł��B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
// �@- Key����
//   - �����̕\��
//�E�Q�[���v���O���~���O
//   - �f�o�b�O�\��(DebugDraw)
//   - �L�����N�^����
// �@- �e�̔���
//�EC/C++����
//   - bool�㐔

/*Dxlib�̃G���g���[�|�C���g*/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�摜�̓ǂݍ���*/
	int drawHandle = LoadGraph("Chara.png");

	//Player�ϐ�
	int pPosX = 100;
	int pPosY = 300;
	int pSpeed = 2;
	//Bullet�ϐ�
	int bPosX = pPosX;
	int bPosY = pPosY;
	int bSpeed = 8;
	bool isBullet = false;

	/*�Q�[�����[�v��*/
	while (TRUE)
	{
		//����ʂ̏�����(�_�u���o�b�t�@�����O1)
		ClearDrawScreen();

		/*Key���͂̎擾*/
		//CheckHitKey�ɑΉ��L�[�̐��l�����邱�ƂŎg��(�ڍׂ̓��t�@�����X)�B

		//Player�̈ړ�
		if (CheckHitKey(KEY_INPUT_W))//W�ŏ�ړ�
		{
			pPosY -= pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_S))//S�ŉ��ړ�
		{
			pPosY += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_D))//D�ŉE�ړ�
		{
			pPosX += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_A))//A�ō��ړ�
		{
			pPosX -= pSpeed;
		}

		//�e�̔���
		if (CheckHitKey(KEY_INPUT_RETURN) && isBullet==false)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			isBullet = true;
		}
		//�e�̈ړ�
		if (isBullet)
		{
			bPosX += bSpeed;
		}
		//�e�̈ʒu������
		if (bPosX>1280)//��ʊO�ɏo����
		{
			bPosX = pPosX;
			bPosY = pPosY;
			isBullet = false;
		}

		/*Draw*/
		DrawGraph(pPosX,pPosY,drawHandle,1);//�L�����N�^�`��
		if (isBullet)//�e�̕`��
		{
			DrawCircle(bPosX,bPosY,4,GetColor(255,255,255),1);//GetColor�̓J���[�R�[�h�ŐF���w��ł���
		}

		/*DebugDraw*/
		//�Q�[���v���C�ɂ͒��ڕK�v�ł͂Ȃ����A�J�����ɂ͕K�v�ȓ��e��\�����Ă���B
		DrawString(0, 0,"�������:WASD�ŏ㍶���E,Enter�Ŕ���",GetColor(255,0,0));//�������\������֐�

		//����ʂ�\��(�_�u���o�b�t�@�����O3)
		ScreenFlip();
		/*���t���b�V������(-1�Ȃ�G���[)*/
		if (ProcessMessage() < 0) { break; }
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}