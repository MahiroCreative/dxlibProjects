#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib����������*/
	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE); 
	//��ʃT�C�Y�ύX
	SetGraphMode(1280, 720, 32);
	//�c�w���C�u����������(�G���[���ɏI��)
	if (DxLib_Init() == -1){return -1;}

	/*�Q�[������*/
	// �_��ł�
	DrawPixel(320, 240, GetColor(255, 255, 255));
	// �L�[���͑҂�
	WaitKey();				
	// �c�w���C�u�����g�p�̏I������
	DxLib_End();				

	return 0;
}