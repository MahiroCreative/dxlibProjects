#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1;}//Dxlib������

	/*�Q�[����*/
	WaitKey();// �L�[���͑҂�


	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}