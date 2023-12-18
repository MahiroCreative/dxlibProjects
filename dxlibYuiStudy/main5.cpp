#include "DxLib.h"

/*�萔(k�͒萔Konstant���Ӗ�����)*/
namespace
{
	constexpr int SHOT = 20;
	constexpr int ScreenSizeX = 1280;
	constexpr int ScreenSizeY = 720;
}

/*�\���̐錾*/
struct Position
{
	int x = 0;
	int y = 0;
};
struct Size
{
	int w = 0;
	int h = 0;
};
struct Player
{
	int handle = -1;
	Position pos;
	Size size;

	bool isPrevshot = false;
};
struct Enemy
{
	int handle = -1;
	int damageHandle = -1;
	Position pos;
	Size size;

	bool isDamage = false;
	int damageCount = 0;

	bool isRightMove = true;
};
struct Shot
{
	int handle = -1;
	Position pos;
	Size size;

	bool isExist = false;
};

/*�O���[�o���ϐ�*/
Player player;
Enemy enemy;
Shot shot[SHOT];

// �v���C���[�̏���������
void InitializePlayer()
{
	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	player.handle = LoadGraph("Resources/player.png");
	// �v���C���[�̃O���t�T�C�Y�𓾂�
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	//Pos
	player.pos.x = 288;
	player.pos.y = 400;
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(�����ꂢ�Ȃ�)����
	player.isPrevshot = false;
}

// �G�l�~�[�̏���������
void InitializeEnemy()
{
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	enemy.handle = LoadGraph("Resources/enemy.png");
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���_���[�W���̏�ԊǗ��p�̕ϐ���������
	enemy.damageHandle = LoadGraph("Resources/enemyDamage.png");
	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�	
	GetGraphSize(enemy.handle, &enemy.size.w, &enemy.size.h);
	//Pos
	enemy.pos.x = 0;
	enemy.pos.y = 50;
	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
	enemy.isDamage = false;
	enemy.damageCount = 0;
	// �G�l�~�[���E�ړ����Ă��邩�ǂ����̃t���O�����Z�b�g
	enemy.isRightMove = true;
}

// �V���b�g�̏���������
void InitializeShot()
{
	int shotHandle = LoadGraph("Resources/shot.png");
	int sizeW, sizeH;
	GetGraphSize(shotHandle, &sizeW, &sizeH);
	for (int i = 0; i < SHOT; i++)
	{
		// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h.
		shot[i].handle = shotHandle;
		// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
		shot[i].isExist = false;
		// �e�̃O���t�B�b�N�̃T�C�Y������
		shot[i].size.w = sizeW;
		shot[i].size.h = sizeH;
	}
}

// �v���C���[�̍X�V
void UpdatePlayer()
{
	// ���L�[�������Ă�����v���C���[���ړ�������
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

	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
		if (player.isPrevshot == false)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < SHOT; i++)
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

	// �v���C���[����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
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

// �G�l�~�[�̍X�V����
void UpdateEnemy()
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

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
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

// �e�̍X�V����
void UpdateShot()
{
	for (int i = 0; i < SHOT; i++)
	{
		// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
		if (shot[i].isExist == true)
		{
			// �ei��8�h�b�g��Ɉړ�������
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
}

// �v���C���[�̕`�揈��
void DrawPlayer()
{
	// �v���C���[��`��
	DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);
}

// �G�l�~�[�̕`�揈��
void DrawEnemy()
{
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
			// �w�c��ł��Ȃ��x��\���O����
			enemy.isDamage = 0;
		}
	}
	else
	{
		DrawGraph(enemy.pos.x, enemy.pos.y, enemy.handle, FALSE);
	}
}

// �e�̕`�揈��
void DrawShot()
{
	for (int i = 0; i < SHOT; i++)
	{
		if (shot[i].isExist)
		{
			// ��ʂɒei��`�悷��
			DrawGraph(shot[i].pos.x, shot[i].pos.y, shot[i].handle, FALSE);
		}
	}
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*����������*/
	// �v���C���[
	InitializePlayer();
	// �G�l�~�[
	InitializeEnemy();
	// �V���b�g
	InitializeShot();

	/*�Q�[�����[�v.*/
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//Update
		UpdatePlayer();
		UpdateEnemy();
		UpdateShot();

		// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
		DrawShot();
		DrawPlayer();
		DrawEnemy();
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

	/*�I������*/
	DxLib::DxLib_End();//Dxlib�I������
	return 0;//�I��
}