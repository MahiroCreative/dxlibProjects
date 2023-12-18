#include <DxLib.h>
#include "Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	//SetDrawScreen�ŕ`��Ώۂɂł���O���t�B�b�N�n���h�����쐬����
	int screen = MakeScreen(ScreenSizeX, ScreenSizeY, true);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		//ClearDrawScreen();

		// �Q�[���̏���
		SetDrawScreen(screen);

		// screen�ɕ`�悷��
		// ��ʂ��N���A���Ă��Ȃ��̂őO�̏�Ԃɏ㏑������Đ���������

		// ��ʂ𕢂�������(6.25%���炢�̕s�����x)�̎l�p��`�悵�Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16);
		DrawBox(0, 0,ScreenSizeX , ScreenSizeY, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �}�E�X�̌��݈ʒu�ƁA���N���b�N��������Ă��邩���`�F�b�N
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		bool isLeft = (GetMouseInput() & MOUSE_INPUT_LEFT);

		// ���N���b�N��������Ă�����ۂ�`�悷��
		if (isLeft)
		{
			DrawCircle(mouseX, mouseY, 8, 0xffff00, true);
		}

		// �f�t�H���g�̃o�b�N�o�b�t�@�ւ̏������݂ɖ߂�
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		DrawGraph(0, 0, screen, true);
		//DrawCircle(mouseX, mouseY, 8, 0xff0000, true);

		//// 10�i�A16�i�\�L�̕��K
		//int x = 10;		// 10�i����10�A16�i����a������
		//int y = 0x10;	// 0x�Ŏn�܂鐔����16�i��
		//				// 16�i����10�A10�i����16������
		//DrawFormatString(10,  0, 0xffffff, "%d", x);	// 10
		//DrawFormatString(10, 16, 0xffffff, "%d", y);	// 16
		//DrawFormatString(10, 32, 0xffffff, "0x%x", x);	// 0xa
		//DrawFormatString(10, 48, 0xffffff, "0x%x", y);	// 0x10


		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		// 16.66ms(16667�}�C�N���b)�o�߂���܂ő҂�
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	DeleteGraph(screen);
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}