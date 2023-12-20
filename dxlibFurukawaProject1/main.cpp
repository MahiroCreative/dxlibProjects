#include <DxLib.h>
#include <cassert>
#include "SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib�J�n����*/
	ChangeWindowMode(true);
	SetGraphMode(Game::kScreenWidht, Game::kScreenHeight, 32);
	if (DxLib_Init() == -1) { return -1; }
	SetDrawScreen(DX_SCREEN_BACK);

	/*�V�[���}�l�[�W���[�̍쐬*/
	SceneManager scene;
	scene.Init();

	/*�Q�[�����[�v*/
	while (ProcessMessage() != -1)
	{
		//�^�C�}�[�̍쐬�ƍX�V(�N��������̎��Ԃ�����)
		LONGLONG start = GetNowHiPerformanceCount();

		//��ʃN���A
		ClearDrawScreen();

		//�����X�V
		scene.Update();

		//��ʍX�V
		scene.Draw();

		//��ʍX�V�̊m��
		ScreenFlip();

		//escKey�̊m�F(���[�v�E�o)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		//�t���[�����[�g�̌Œ�(FPS6016.66ms)
		while (GetNowHiPerformanceCount() - start < 16667);
	}

	/*�V�[���̏I������*/
	scene.End();

	/*Dxlib�I��*/
	DxLib_End();
	return 0;
}