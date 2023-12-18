#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "Enemy1.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(kScreenSizeX, kScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	// �O���t�B�b�N���\�[�X�̃��[�h
//	int enemyHandle = LoadGraph("data/teki.png");	// �t�@�C�����ԈႢ
	int enemyHandle = LoadGraph("data/enemy.png");
	assert(enemyHandle != -1);	// �t�@�C���̃��[�h�Ɏ��s����Ǝ~�܂�

	Enemy enemy[kEnemyNum];
	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i].Init();
		enemy[i].SetHandle(enemyHandle);
		enemy[i].SetStartPos();
	}

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].Update();
		}

		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].Draw();
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		//FPS�Œ�(16.66ms)
		while (GetNowHiPerformanceCount() - start < 16667) {}

		/*���荞�ݏ���(Esc:�I������)*/
		if (ProcessMessage() < 0)
		{
			//�}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			//Esc�ł�������
			break;
		}
	}


	/*Dxlib�I������*/
	DeleteGraph(enemyHandle);//�O���t�B�b�N��������������
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I��
}