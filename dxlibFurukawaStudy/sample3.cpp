#include <DxLib.h>
#include "SceneMain3.h"

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

	// �������𖾎��I�Ɋm�ۂ���
	// new ���g�p���ă��������m�ۂ��邱�Ƃ�
	// �q�[�v�̈�Ƀ��������m�ۂ��邱�Ƃ��ł���
	// new�̓��������m�ۂ��A�ǂ��Ƀ��������m�ۂ������A��
	// �A�h���X��Ԃ��Ă����
	SceneMain* pMain = new SceneMain;
	pMain->Init();

	SceneMain scene;	// �X�^�b�N�̈�Ƀ������m�ۂ���Ă���
	scene.Init();

		// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		pMain->Update();
		scene.Update();

		pMain->Draw();
		scene.Draw();


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

	// �m�ۂ������������������
	delete pMain;
	pMain = nullptr;

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}