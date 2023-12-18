#include "DxLib.h"

/*�R��Fclass1*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*���W�ݒ�*/
	// x���W.
	int x = 0;
	//y���W
	int y[10];
	for (int i = 0; i < 10; i++)
	{
		y[i] = i * 48;//48�Y����
	}

	/*�Q�[�����[�v*/
	while (ProcessMessage() > -1)
	{
		/*��ʏ�����*/
		ClearDrawScreen();

		/*�Q�[������*/
		// ���L�[�́�����������E�ɓ�����.
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x++;
		}

		/*�`��̍X�V*/
		for (int i = 0; i < 10; i++)
		{
			LoadGraphScreen(x, y[i], "Resources/player.png", FALSE);
		}
		ScreenFlip();//���ō쐬������ʂ�\��

		/*���[�v�I������*/
		if (ProcessMessage() < 0)//�G���[����
		{
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))//Esc�ł��I������
		{
			break;
		}
	}

	/*�I������*/
	DxLib::DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}
