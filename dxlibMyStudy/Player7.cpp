#include <DxLib.h>
#include "Player7.h"
#include "Shot7.h"
#include "Game.h"

void InitPlayer(Player& player)
{
	player.handle = LoadGraph("Resources/player.png");
	player.x = 288;
	player.y = 400;
	GetGraphSize(player.handle, &player.w, &player.h);

	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(�����ꂢ�Ȃ�)����
	player.isPrevshot = false;
}

void UpdatePlayer(Player& player, Shot shot[], int shotArrayNum)
{
	// ���L�[�������Ă�����v���C���[���ړ�������
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		player.y -= 3;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.y += 3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.x -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.x += 3;
	}

	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
		if (player.isPrevshot == false)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < shotArrayNum; i++)
			{
				// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
				if (shot[i].isShot == false)
				{
					// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
					shot[i].x = (player.w - shot[i].w) / 2 + player.x;
					shot[i].y = (player.h - shot[i].h) / 2 + player.y;

					// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
					shot[i].isShot = true;

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
	if (player.x < 0)
	{
		player.x = 0;
	}
	if (player.x > ScreenSizeX - 64)
	{
		player.x = ScreenSizeX - 64;
	}
	if (player.y < 0)
	{
		player.y = 0;
	}
	if (player.y > ScreenSizeY - 64)
	{
		player.y = ScreenSizeY - 64;
	}
}

void DrawPlayer(Player& player)
{
	// �v���C���[��`��
	DrawGraph(player.x, player.y, player.handle, FALSE);
}
