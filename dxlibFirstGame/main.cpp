#include "DxLib.h"
#include "GameCommon.h"
#include "SceneBase.h"
#include "SceneMain.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(GameConst::ScreenSizeX, GameConst::ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1;}//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�ϐ�*/
	LONGLONG roopStartTime;
	SceneMain* scene = new SceneMain();

	/*�Q�[�����[�v��*/
	while(true)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/
		scene->Update();
		scene->Draw();



		//����ʂ�\��
		ScreenFlip();

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }

		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		//fps�Œ�(60fps:16.66ms)
		//���[�v�J�n��������16.66ms�o�܂Œ�~
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}

	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}