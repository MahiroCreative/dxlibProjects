#include "DxLib.h"

/*�萔(k�͒萔Konstant���Ӗ�����)*/
namespace
{
	constexpr int ScreenSizeX = 1280;
	constexpr int ScreenSizeY = 720;
	constexpr int kShotNum = 20;//�ő�e��
}

/*�\���̐錾*/
//�I�u�W�F�N�g�̈ʒu
struct Position
{
	int x = 0;
	int y = 0;
};
//�I�u�W�F�N�g�̑傫��
struct Size
{
	int w = 0;
	int h = 0;
};
//Player�\����(Player�ϐ�)
struct Player
{
	//�摜�E�ʒu�E�T�C�Y
	int handle = -1;
	Position pos;
	Size size;
	//Shot�������Ă���Œ���
	bool isPrevshot = false;
};
//Enemy�\����(Enemy�ϐ�)
struct Enemy
{
	//�摜�E�ʒu�E�T�C�Y
	int handle = -1;
	int damageHandle = -1;
	Position pos;
	Size size;
	//�_���[�W���󂯂Ă���Œ���
	bool isDamage = false;
	//�_���[�W������󂯂���
	int damageCount = 0;
	//�ړ���������
	bool isRightMove = true;
};
//Shot�\����
struct Shot
{
	//�摜�E�ʒu�E�T�C�Y
	int handle = -1;
	Position pos;
	Size size;
	//���������݂��Ă��邩
	bool isExist = false;
};

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*�e�\���̍쐬*/
	Player player;
	Enemy enemy;
	Shot shot[kShotNum];

	/*�摜�ǂݍ���*/
	player.handle = LoadGraph("Resources/player.png");
	enemy.handle = LoadGraph("Resources/enemy.png");
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");
	int shotHandle = LoadGraph("Resources/shot.png");

	/*���W�ݒ�*/
	//Player
	player.pos.x = 288;
	player.pos.y = 400;
	//Enemy
	enemy.pos.x = 0;
	enemy.pos.y = 50;

	/*�e�I�u�W�F�N�g�̃O���t�B�b�N�T�C�Y*/
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);

	/*�t���O������*/
	//Player
	player.isPrevshot = false;
	//Enemy
	enemy.isDamage = false;
	enemy.damageCount = 0;
	enemy.isRightMove = true;
	//Shot
	for (int i = 0; i < kShotNum; i++)
	{
		// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h.
		shot[i].handle = shotHandle;
		// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
		shot[i].isExist = false;
		// �e�̃O���t�B�b�N�̃T�C�Y������
		shot[i].size.w = sizeW;
		shot[i].size.h = sizeH;
	}

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
				player.pos.y -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				player.pos.y += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				player.pos.x -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				player.pos.x += 3;
			}

			// �e�̔��ˏ���(SPACE)
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
				if (player.isPrevshot == false)
				{
					// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
					for (int i = 0; i < kShotNum; i++)
					{
						// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (shot[i].isExist == false)
						{
							// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
							shot[i].pos.x = (player.size.w - shot[i].size.w) / 2 + player.pos.x;
							shot[i].pos.y = (player.size.h - shot[i].size.h) / 2 + player.pos.y;

							// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
							shot[i].isExist = true;

							// ��e���o�����̂Œe���o�����[�v���甲���܂�
							break;
						}
					}
				}

				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���true(������Ă���)����
				player.isPrevshot = true;
			}
			else
			{
				// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���false(������Ă��Ȃ�)����
				player.isPrevshot = false;
			}

			//��ʊO�ɏo�Ȃ��悤�ɂ���
			if (player.pos.x < 0)
			{
				player.pos.x = 0;
			}
			if (player.pos.x > ScreenSizeX - player.size.w)
			{
				player.pos.x = ScreenSizeX - player.size.w;
			}
			if (player.pos.y < 0)
			{
				player.pos.y = 0;
			}
			if (player.pos.y > ScreenSizeY - player.size.h)
			{
				player.pos.y = ScreenSizeY - player.size.h;
			}
		}

		//Enemy����
		{
			// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
			if (enemy.isRightMove == true)
			{
				enemy.pos.x += 3;
			}
			else
			{
				enemy.pos.x -= 3;
			}

			// ��ʊO�ɏo�Ȃ��悤�ɂ��A�[�ɂȂ����甽�]
			if (enemy.pos.x > ScreenSizeX - enemy.size.w)
			{
				enemy.pos.x = ScreenSizeX - enemy.size.w;
				enemy.isRightMove = false;
			}
			else if (enemy.pos.x < 0)
			{
				enemy.pos.x = 0;
				enemy.isRightMove = true;
			}
		}

		//�e�̏���
		for (int i = 0; i < kShotNum; i++)
		{
			// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
			if (shot[i].isExist == true)
			{
				// �ei���P�U�h�b�g��Ɉړ�������
				shot[i].pos.y -= 8;

				// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
				if (shot[i].pos.y < 0 - shot[i].size.h)
				{
					shot[i].isExist = false;
				}
			}

			// �e�̂����蔻��.
			// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
			if (shot[i].isExist == 1)
			{
				// �G�l�~�[�Ƃ̓����蔻��
				if (((shot[i].pos.x > enemy.pos.x && shot[i].pos.x < enemy.pos.x + enemy.size.w) ||
					(enemy.pos.x > shot[i].pos.x && enemy.pos.x < shot[i].pos.x + shot[i].size.w)) &&
					((shot[i].pos.y > enemy.pos.y && shot[i].pos.y < enemy.pos.y + enemy.size.h) ||
						(enemy.pos.y > shot[i].pos.y && enemy.pos.y < shot[i].pos.y + shot[i].size.h)))
				{
					// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					shot[i].isExist = 0;

					// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
					enemy.isDamage = true;

					// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					enemy.damageCount = 0;
				}
			}
		}

		/*�`��̍X�V(�`�揇�����̂܂܃��C���[��)*/
		DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);//Player�`��
		// �G�l�~�[��`��
		// ���c�߂Ă��邩�ǂ����ŏ����𕪊�
		if (enemy.isDamage == true)
		{
			// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
			DrawGraph(enemy.pos.x, enemy.pos.y, enemy.damageHandle, FALSE);

			// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
			enemy.damageCount++;

			// �������c�ߏ��߂� �R�O �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
			// ���ɖ߂��Ă�����
			if (enemy.damageCount == 30)
			{
				// �w�c��ł��Ȃ��x��\��
				enemy.isDamage = false;
			}
		}
		else
		{
			DrawGraph(enemy.pos.x, enemy.pos.y, enemy.handle, FALSE);
		}
		//�e�̏���
		for (int i = 0; i < kShotNum; i++)
		{
			// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
			if (shot[i].isExist == true)
			{
				// ��ʂɒei��`�悷��
				DrawGraph(shot[i].pos.x, shot[i].pos.y, shot[i].handle, FALSE);
			}
		}
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