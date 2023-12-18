#include "DxLib.h"
#include "Player7.h"
#include "Shot7.h"
#include "Enemy7.h"
#include "Game7.h"

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*�Q�[���I�u�W�F�N�g�̍쐬*/
	Player player;
	Enemy enemy;
	Shot shot[ShotNum];

	/*�I�u�W�F�N�g������*/
	InitPlayer(player);
	InitEnemy(enemy);
	int shotGraph, sizeW, sizeH;
	shotGraph = LoadGraph("Resources/shot.png");//�e�̉摜
	GetGraphSize(shotGraph, &sizeW, &sizeH);//�e�T�C�Y
	for (int i = 0; i < ShotNum; i++)//�S�Ă̒e��������
	{
		InitShot(shot[i], shotGraph, sizeW, sizeH);
	}


	// �Q�[�����[�v.
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//------------------------------//
		// �v���C���[���[�`��
		//------------------------------//
		UpdatePlayer(player, shot, ShotNum);
		DrawPlayer(player);

		//------------------------------//
		// �G�l�~�[���[�`��
		//------------------------------//
		UpdateEnemy(enemy);
		DrawEnemy(enemy);

		//------------------------------//
		// �e���[�`��
		//------------------------------//
		for (int i = 0; i < ShotNum; i++)
		{
			UpdateShot(shot[i], enemy);
			DrawShot(shot[i]);
		}

		// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
		ScreenFlip();


		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0)
		{
			break;
		}
		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}