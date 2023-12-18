#include "DxLib.h"

/*�R��Fclass1*/

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1;}//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*���\�[�X�ǂݍ���*/
	int playerGraph = LoadGraph("Resources/player.png");//Player
	int enemyGraph = LoadGraph("Resources/enemy.png");//Enemy

	/*Player�Z�b�e�B���O*/
	//�����ʒu
	int playerX = 280;
	int playerY = 400;

	/*Enemy�Z�b�e�B���O*/
	//�����ʒu
	int enemyX = 320;
	int enemyY = 240;
	//�ړ���
	int enemyMoveX = 3;


	/*�Q�[�����[�v*/
	while (true)
	{
		/*��ʏ�����(�^���Âɂ���)*/
		ClearDrawScreen();

		/*�Q�[������*/
		//Player����
		{
			//Key���͂ɂ��ړ�
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				playerY -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				playerY += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				playerX -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				playerX += 3;
			}

			//��ʊO�ɏo�Ȃ��悤�ɂ���
			if (playerX < 0)
			{
				playerX = 0;
			}
			if (playerX > 1280 - 64)
			{
				playerX = 1280 - 64;
			}
			if (playerY < 0)
			{
				playerY = 0;
			}
			if (playerY > 720 - 64)
			{
				playerY = 720 - 64;
			}

		}
		//Enemy����
		{
			//�ړ�
			enemyX += enemyMoveX;

			// ��ʊO�ɏo�Ȃ��悤�ɂ���
			if (enemyX < 0)
			{
				enemyMoveX = 3;
				enemyX = 0;
			}
			if (enemyX > 1280 - 64)
			{
				enemyMoveX = -3;//�ړ��̔��]
				enemyX = 1280 - 64;
			}
		}



		/*�`��̍X�V*/
		DrawGraph(playerX, playerY, playerGraph, FALSE);//Player�`��
		DrawGraph(enemyX, enemyY, enemyGraph, FALSE);//�G��`��
		ScreenFlip();//���ō쐬������ʂ�\��

		/*���[�v�I������*/
		if (ProcessMessage() < 0)//�G���[����
		{
			break;
		}
		else if (CheckHitKey(KEY_INPUT_ESCAPE))//Esc�ł��I������
		{
			break;
		}
	}


	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}