#include <DxLib.h>
#include <cassert>
#include <cmath>

/*�T�v*/
//�T�C���R�T�C���ȂǁB

/// <summary>
/// �x���@�Ŏw�肵���p�x���ʓx�@�ɕϊ�����
/// </summary>
/// <param name="deg">�x���@�̊p�x</param>
/// <returns>�ʓx�@�̊p�x</returns>
double DegToRad(double deg)
{
	return DX_PI / 180 * deg;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	int handle = LoadGraph("data/arrow.png");
	assert(handle != -1);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���

		// �~����DXLIB��#define�Œ�`���Ă���Ă���̂�
		// DxLib�ŃQ�[�������Ƃ��͂�����g�����I

		// DX_PI		double�^
		// DX_PI_F		float�^
		// DX_TWO_PI	DX_PI��2�{
		// DX_TWO_PI_F	DX_PI_F��2�{

		// 0�x����45�x����]6�`��
		for (int i = 0; i < 6; i++)
		{
			DrawRotaGraph(64 + 96 * i, 64,
				1.0,	// �g�嗦
				DegToRad(i * 45.0),	// ��]
				handle, true, false);
		}



		for (int i = 0; i < 6; i++)
		{
			int startX = 64 + 96 * i;
			int startY = 64 + 128;

			// ���S�_
			DrawCircle(startX,
				startY,
				2, 0xffff00, true);

			// ���S�_�����ɕ\������Ă�����Ɠ���������
			// ����32�̐�����������

			// ����L�΂�����
			double angle = DegToRad(i * 45);
			double moveX = 32 * cosf(angle);
			double moveY = 32 * sinf(angle);

			int endX = startX + static_cast<int>(moveX);
			int endY = startY + static_cast<int>(moveY);
			DrawLine(startX, startY,
				endX,
				endY,
				0xffffff);
		}

		// ��]�f��
		{
			int startX = 320;
			int startY = 400;

			DrawBox(startX - 64, startY - 64,
				startX + 65, startY + 65,
				0xff0000, false);

			DrawCircle(startX, startY, 64,
				0x00ff00, false);


			// ���S�_
			DrawCircle(startX,
				startY,
				2, 0xffff00, true);

			// tempAngle�̕����ɐL�т��������
			static double tempAngle = 0.0;
			tempAngle += 0.02;

			// �����L�т�������擾����
			// cos��X�����Asin��Y�������擾����
			double moveX = 64 * cosf(tempAngle);
			double moveY = 64 * sinf(tempAngle);

			// �J�n�_�̍��W�𑫂��ďI�_�̍��W��
			int endX = startX + static_cast<int>(moveX);
			int endY = startY + static_cast<int>(moveY);

			DrawLine(startX, startY,
				endX,
				endY,
				0xffffff);
		}


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

	DeleteGraph(handle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}