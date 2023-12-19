#include <DxLib.h>
#include <cassert>

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

	int handle = LoadGraph("data/hana.jpg");
	assert(handle != -1);

	int fadeAlpha = 255;	// �s��������n�߂�
	int fadeSpeed = -1;		// �����x�����߂�
	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���

		fadeAlpha += fadeSpeed;
		// 0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		if (fadeAlpha < 0)
		{
			// ���S�Ƀt�F�[�h�C������
			fadeAlpha = 0;
			// ���̃t���[������̓t�F�[�h�A�E�g
			fadeSpeed = 1;
		}
		// 255�ȉ��ɂȂ�Ȃ��悤�ɂ���
		if (fadeAlpha > 255)
		{
			// ���S�Ƀt�F�[�h�A�E�g����
			fadeAlpha = 255;
			fadeSpeed = -1;
		}



		// ��1�����@DX_BLENDMODE_ALPHA: �������ŕ\�������I
		// ��2�����@DX_BLENDMODE_ALPHA���w�肵�Ă���ꍇ�A
		//			�ǂ�ʂ̓����x�ŕ\�����邩�A���w�肷�� 0~255
		//			0:���S�ɓ���	255:�s����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(0, 0, handle, false);

		// SetDrawBlendMode�œ����ɂ��������̂�\��������A
		// �ȍ~�̕��̂��������ɂȂ�Ȃ��悤�A
		// DX_BLENDMODE_NOBLEND�ɖ߂��Ă���
		// ��2�����͉����w�肵�Ă�����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// SetDrawBlendMode�Ŕ������ɂ������I�Ǝw�肷��ƁA
		// �ȍ~���ׂĂ̂��̂����������x�ŕ\�������
		DrawBox(0, 0, 640, 240, GetColor(255, 255, 0), true);

		// �t�F�[�h�C�� ����255����0�ɕω�������
		// �t�F�[�h�p�̍��l�p��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


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