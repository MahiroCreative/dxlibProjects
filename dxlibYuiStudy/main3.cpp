#include "DxLib.h"

/*�萔(k�͒萔Konstant���Ӗ�����)*/
namespace
{
	constexpr int kShotNum = 3;//��ʏ�̍ő�e��
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*���\�[�X�ǂݍ���*/
	int playerGraph = LoadGraph("Resources/player.png");//Player
	int enemyGraph = LoadGraph("Resources/enemy.png");//Enemy
	int shotGraph = LoadGraph("Resources/shot.png");//Shot

	/*Player�Z�b�e�B���O*/
	//�����ʒu
	int playerX = 280;
	int playerY = 400;

	/*Enemy�Z�b�e�B���O*/
	//�����ʒu
	int enemyX = 0;
	int enemyY = 50;
	bool enemyRightMove = true;//�G�l�~�[���E�ړ����Ă��邩�ǂ���

	/*Shot�Z�b�e�B���O*/
	//�ʒu�̏�����
	int shotX[kShotNum] = { 0 };
	int shotY[kShotNum] = { 0 };
	bool shotFlag[kShotNum] = { false };//Shot�����݂��邩

	/*Other*/
	bool isHitSpace = false;//�O��L�[��������Ă��邩

	/*�Q�[�����[�v*/
	while (1)
	{
		/*��ʏ�����*/
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

			// �e�̔��ˏ���(SPACE)
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				//Space����������ςȂ��łȂ��Ȃ�A�o��B
				if (!isHitSpace)
				{
					//Space��������ςȂ������m����t���O
					isHitSpace = true;

					//�e�̐�������
					for (int i = 0; i < kShotNum; i++)
					{
						// �e�͍ő�3���Ȃ̂ŁA�]���Ă�g������΂����ɐ���
						if (shotFlag[i] == false)
						{
							int Bw, Bh, Sw, Sh;

							// �v���C���[�ƒe�̉摜�̃T�C�Y�𓾂�
							GetGraphSize(playerGraph, &Bw, &Bh);
							GetGraphSize(shotGraph, &Sw, &Sh);

							// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
							shotX[i] = (Bw - Sw) / 2 + playerX;
							shotY[i] = (Bh - Sh) / 2 + playerY;

							// �ei�͌����_�������đ��݂���̂Ńt���O�𗧂Ă�B
							shotFlag[i] = true;

							break;
						}
					}
				}
			}
			else
			{
				//Space��������Ă��Ȃ��Ȃ�A�t���O��߂��B
				isHitSpace = false;
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
			// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
			if (enemyRightMove == true)
			{
				enemyX += 3;
			}
			else
			{
				enemyX -= 3;
			}

			// ��ʊO�ɏo�Ȃ��悤�ɂ��A�[�ɂȂ����甽�]
			if (enemyX > 1280 - 64)
			{
				enemyX = 1280 - 64;
				enemyRightMove = false;
			}
			else if (enemyX < 0)
			{
				enemyX = 0;
				enemyRightMove = true;
			}
		}

		//Shot����
		//�e�̈ړ����[�`��(�e�����݂��Ă���ꍇ�̂ݏ�����)
		for (int i = 0; i < kShotNum; i++)
		{
			if (shotFlag[i] == true)
			{
				// �ei��8�h�b�g��Ɉړ�������
				shotY[i] -= 4;

				// ��ʊO�ɏo���ꍇ�͑��݂�false(���݂��Ȃ�)�ɂ���
				if (shotY[i] < -80)
				{
					shotFlag[i] = false;
				}				
			}
		}

		/*�`��̍X�V(�`�揇�����̂܂܃��C���[��)*/
		//Shot�̕`��
		for (int i = 0; i < kShotNum; i++)//�S�Ă̒e�g�ɏ���
		{
			if (shotFlag[i] == true) //���݂��Ă���e�����`��
			{
				DxLib::DrawGraph(shotX[i], shotY[i], shotGraph, FALSE);
			}
		}
		DxLib::DrawGraph(playerX, playerY, playerGraph, FALSE);//Player�`��
		DxLib::DrawGraph(enemyX, enemyY, enemyGraph, FALSE);//�G��`��
		DxLib::ScreenFlip();//���ō쐬������ʂ�\��

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
	DxLib::DxLib_End();//Dxlib�I������
	return 0;//�I��
}