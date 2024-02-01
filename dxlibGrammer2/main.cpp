#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//�������A���̃V���[�Y�ŉ��������e�͕K�v�K�v�A�Ƃ������x���ł��B�������o�܂��B
//Dxlib�̃��t�@�����X��p�ɂɌ��Ċ֐��ɈӖ��Ȃǂ��m�F���Ȃ���i�߂�̂��������g�����ł��B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
// �@- �~�̓����蔻��

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�摜�̓ǂݍ���*/
	int drawHandle = LoadGraph("Chara.png");

	/*�ϐ�*/
	//Player�ϐ�
	int pPosX = 100;
	int pPosY = 300;
	int pSpeed = 2;
	//Bullet�ϐ�
	int bPosX = pPosX;
	int bPosY = pPosY;
	int bR = 4;
	int bSpeed = 8;
	bool isBullet = false;
	//Enemy�ϐ�
	int ePosX = 1000;
	int ePosY = 360;
	int eR = 64;
	int eSpeed = 8;
	bool isHit = false;

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (TRUE)
	{
		//����ʂ̏�����
		ClearDrawScreen();

		/*Player����*/
		//�ړ�����
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

		/*Bullet����*/
		//�e�̔���
		if (CheckHitKey(KEY_INPUT_RETURN) && isBullet == false)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			isBullet = true;
		}
		//�e�̈ړ�
		if (isBullet)
		{
			bPosX += bSpeed;
		}
		//�e�̈ʒu������
		if (bPosX > 1280)//��ʊO�ɏo����
		{
			bPosX = pPosX;
			bPosY = pPosY;
			isBullet = false;
		}

		/*Enemy����*/



		/*Draw*/
		//�L�����N�^�`��
		//DrawGraph(pPosX, pPosY, drawHandle, 1);
		DrawRotaGraph();
		//�e�̕`��
		if (isBullet)
		{
			DrawCircle(bPosX, bPosY, bR, GetColor(255, 255, 255), 1);
		}
		//�G�l�~�[�`��
		DrawCircle(ePosX, ePosY, eR, GetColor(255, 0, 255), 1);



		//����ʂ�\��
		ScreenFlip();

		//����ʂ�\��(�_�u���o�b�t�@�����O3)
		ScreenFlip();
		/*���t���b�V������(-1�Ȃ�G���[)*/
		if (ProcessMessage() < 0) { break; }
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}