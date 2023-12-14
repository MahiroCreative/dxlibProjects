#include "DxLib.h"
#include "Shot.h"
#include "Player.h"

// �v���C���[�̏���������
void InitializePlayer(Player& player)
{
	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h
	player.handle = LoadGraph("Resources/player.png");
	//�����ʒu
	player.pos.x = 288;
	player.pos.y = 400;
	// �v���C���[�̃O���t�T�C�Y�𓾂�
	GetGraphSize(player.handle, &player.size.w, &player.size.h);
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(�����ꂢ�Ȃ�)����
	player.isPrevshot = false;
}

// �v���C���[�̍X�V
void UpdatePlayer(Player& player, Shot shot[], int shotNum)
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
			for (int i = 0; i < shotNum; i++)
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

// �v���C���[�̕`�揈��
void DrawPlayer(Player& player)
{
	// �v���C���[��`��
	DrawGraph(player.pos.x, player.pos.y, player.handle, FALSE);
}