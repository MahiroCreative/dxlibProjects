#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//�������A���̃V���[�Y�ŉ��������e�͕K�v�K�v�A�Ƃ������x���ł��B�������o�܂��B
//�܂��A���w�Ҍ����̉���̂悤�Ȏ��͂��Ă��܂���B�g�����̗Ⴊ�����Ă�����x�ł��B
//������Ȃ������͎���\���I�ɒ��ׂĉ������B
//Dxlib�̃��t�@�����X��p�ɂɌ��Ċ֐��ɈӖ��Ȃǂ��m�F���Ȃ���i�߂�̂��������g�����ł��B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
// �@�] Key����
//�EC���@
//   - if��

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

	//�ϐ�
	int posX=100;
	int posY=300;

	/*�Q�[�����[�v��*/
	while (TRUE)
	{
		//����ʂ̏�����(�_�u���o�b�t�@�����O1)
		ClearDrawScreen();

		/*Key���͂̎擾*/
		//CheckHitKey�ɑΉ��L�[�̐��l�����邱�ƂŎg��(�ڍׂ̓��t�@�����X)�B
		//�����Enter�������ꂽ���ǂ������擾�B
		if (CheckHitKey(KEY_INPUT_UP))
		{

		}
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{

		}

		
		//����ʂ�\��(�_�u���o�b�t�@�����O3)
		ScreenFlip();
		/*���t���b�V������(-1�Ȃ�G���[)*/
		if (ProcessMessage() < 0) { break; }
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}