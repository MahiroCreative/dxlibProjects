#include <DxLib.h>
#include <cmath>
#include "Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	constexpr float kBarLen = 100;
	constexpr float kCenterX = 320;
	constexpr float kCenterY = 240;
	constexpr float kDegToRad = DX_PI_F / 180.0f;

	int angle = 0;

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		DrawCircle(kCenterX, kCenterY, 2, 0xffffff, true);
		DrawCircle(kCenterX, kCenterY, kBarLen, 0xffffff, false);

		angle++;
		float radian = angle * kDegToRad;

		float offsetX = kBarLen * cosf(radian);
		float offsetY = kBarLen * sinf(radian);
		DrawLine(kCenterX, kCenterY,
			kCenterX + offsetX, kCenterY - offsetY,
			0xff0000);

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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}