#include "DxLib.h"
#include "class3Enemy.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	Enemy enemy;
	enemy.Init();

	// �G�̈ʒu��ύX����
	int x = 120;
	int y = 120;

	// ����͒��ړ���Ă邪���ۂɂ͂��낢�돈�����������ʉ�ʊO�ɂȂ��Ă��܂����z��
	x = -120;
	y = -120;

	enemy.SetPos(x, y);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		enemy.Draw();

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