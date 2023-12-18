#include "Player8.h"

// ������.
void Player::Init()
{
	shotIntervalCount = 0;

	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	Graph = LoadGraph("Resources/EpicPlayer.png");
	X = SCREEN_W / 2;
	Y = SCREEN_H - 100;

	// �v���C���[�ƒe�̉摜�̃T�C�Y�𓾂�
	GetGraphSize(Graph, &W, &H);
}

// �A�b�v�f�[�g.
void Player::Update(Shot shot[], int shotNum)
{
	// ���L�[�������Ă�����v���C���[���ړ�������
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		Y -= PLAYER_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		Y += PLAYER_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		X -= PLAYER_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		X += PLAYER_SPEED;
	}

	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		// �V���b�g��ł̂�҂J�E���g���[���ɂȂ��Ă���e�𔭎�
		if (shotIntervalCount == 0)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < shotNum; i++)
			{
				// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
				if (shot[i].IsVisible() == false)
				{
					int startX = (W - shot[i].GetSizeW()) / 2 + X;
					int startY = (H - shot[i].GetSizeH()) / 2 + Y;

					shot[i].OnShoot(startX, startY);

					// ��e���o�����̂Œe���o�����[�v���甲���܂�
					break;
				}
			}

			// �C���^�[�o���p�̃J�E���^�[��ݒ�.
			shotIntervalCount = SHOT_INTERVAL;
		}
	}

	if (shotIntervalCount != 0)
	{
		--shotIntervalCount;
	}

	// �v���C���[����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
	if (X < 0)
	{
		X = 0;
	}
	if (X > SCREEN_W - W)
	{
		X = SCREEN_W - W;
	}
	if (Y < 0)
	{
		Y = 0;
	}
	if (Y > SCREEN_H - H)
	{
		Y = SCREEN_H - H;
	}
}

// �`��.
void Player::Draw()
{
	DrawGraph(X, Y, Graph, TRUE);
}