//-----------------------------------------------------------------------------
// @brief  ���C������.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Shot.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
//-----------------------------------------------------------------------------
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------


// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	Player player;
	Enemy enemy;
	Shot shot[SHOT];

	// �v���C���[�̏���������
	InitializePlayer(player);

	// �G�l�~�[�̏���������
	InitializeEnemy(enemy);

	// �V���b�g�̏���������
	int shotHandle = LoadGraph("Resources/shot.png");
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);
	for (int i = 0; i < SHOT; i++)
	{
		InitializeShot(shot[i], shotHandle, sizeW, sizeH);
	}

	// �Q�[�����[�v.
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//�v���C���[�̍X�V����
		UpdatePlayer(player, shot, SHOT);
		// �v���C���[�̕`�揈��
		DrawPlayer(player);

		//�G�l�~�[�̍X�V����
		UpdateEnemy(enemy);
		// �G�l�~�[�̕`�揈��
		DrawEnemy(enemy);

		//�e�̍X�V����
		for (int i = 0; i < SHOT; i++)
		{
			UpdateShot(shot[i], enemy);
			// �e�̕`�揈��
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