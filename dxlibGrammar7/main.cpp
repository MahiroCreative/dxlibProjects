#pragma once
//�I�u�W�F�N�g�w�b�_
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
//���L�w�b�_(�ˑ��֌W���������̂قǍŌ�)
#include "MyDxlibCommon.h"
#include "math.h"
#include "DxLib.h"//�����ł��g���̂ōŌ�


/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//���������e�͕K�v�Œ���ł��B�������o�܂��B�܂��ڍׂȉ�������Ă��܂���B
//�������t�@�����X��O���T�C�g���Q�l�ɂ��Ă��������B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�E�Q�[���v���O���~���O
// �@- �I�u�W�F�N�g�w����p�����Q�[���v���O���~���O
//�EC/C++����
//   - �N���X

/*�R�����g*/
//�{���Ȃ�N���X�����ۂ�.h��.cpp�ɕ����邪�A�R�[�h�̊ȕ։��̂��߂ɑS��.h�ɋL�q���Ă���B
//���ۂɃQ�[�����̍ۂɂ�.h��.cpp�ɕ����Ăق����B
//�R���X�g���N�^�Ƃ��A�Q�b�^�[�Ƃ��Z�b�^�[�Ƃ��̉���͂����ł͂��Ȃ��B
//�܂��A�����蔻��̃J���[�R�[�h�ȂǁA�悭�g���萔�Ȃǂ�"Common.h"�ɂ܂Ƃ߂��B


//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(WindowSize::SIZE_X, WindowSize::SIZE_Y, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�Q�[���萔*/
	//Player.
	constexpr int PLAYER_FIRST_POSX = 20;
	constexpr int PLAYER_FIRST_POSY = 360;
	constexpr int PLAYER_R = 8;
	constexpr int PLAYER_SPEED = 3;
	constexpr int PLAYER_SHOT_MAX = 3;
	constexpr int PLAYER_SHOT_R = 2;
	constexpr int PLAYER_SHOT_SPEED = 8;
	//Enemy.
	constexpr int ENEMY_FIRST_POSX = 1100;
	constexpr int ENEMY_FIRST_POSY = 360;
	constexpr int ENEMY_R = 64;
	constexpr int ENEMY_SPEED = 2;
	constexpr int ENEMY_SHOT_R = 24;
	constexpr int ENEMY_SHOT_SPEED = -2;

	/*�Q�[���ϐ�*/
	int playerDrawHandle = LoadGraph("Chara.png");
	int enemyShotSpeed = 4;
	int enemyShotSize = 32;
	int delSpeed = 1;
	int delSize = 4;

	/*�f�o�b�O�p�ϐ�*/
	int debugNum = 0;
	int debugNum2 = 0;

	/*�|�C���^�̍쐬*/
	//�N���X�͊�{�I�Ƀ|�C���^�ŉ^�p����B
	Player* pPlayer;
	Enemy* pEnemy;
	Bullet* pPBullet[PLAYER_SHOT_MAX];
	Bullet* pEBullet;

	/*�C���X�^���X�̍쐬*/
	pPlayer = new Player;
	pEnemy = new Enemy;
	pEBullet = new Bullet;
	//PlayerBullet.
	for (int i = 0; i < PLAYER_SHOT_MAX; i++)
	{
		pPBullet[i] = new Bullet;//�C���X�^���X����
	}

	/*������(Player��Enemy�̂�)*/
	pPlayer->Init(LoadGraph("Chara.png"), PLAYER_FIRST_POSX, PLAYER_FIRST_POSY, PLAYER_R, PLAYER_SPEED, true, true);
	pEnemy->Init(ENEMY_FIRST_POSX, ENEMY_FIRST_POSY, ENEMY_R, ENEMY_SPEED, true);

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();
		//����ʂ̏�����
		ClearDrawScreen();

		/*Update*/
		//player.
		pPlayer->Update();
		//enemy.
		pEnemy->Update();
		//eBullet.
		if (pEBullet->getVisible())
		{
			pEBullet->Update();
		}
		//pBulet.
		for (int i = 0; i < PLAYER_SHOT_MAX; i++)
		{
			if (pPBullet[i]->getVisible())
			{
				pPBullet[i]->Update();
			}

		}

		/*�e�ۂ̔���*/
		//Player.
		if (pPlayer->getShotFlag())
		{
			for (int i = 0; i < PLAYER_SHOT_MAX; i++)
			{
				if (!pPBullet[i]->getVisible())
				{
					pPBullet[i]->Init(pPlayer->X, pPlayer->Y, PLAYER_SHOT_R, PLAYER_SHOT_SPEED, ColorCode::MAGENTA, true);
					break;
				}
			}
		}
		//Enemy.
		//��ʂ���o����e����������̂ŁA���̍ۂɍĔ���
		if (!pEBullet->getVisible())
		{
			pEBullet->Init(pEnemy->X, pEnemy->Y, enemyShotSize, -enemyShotSpeed, ColorCode::LIME, true);
			//�e�̑��x�ƃT�C�Y�̍X�V
			enemyShotSpeed += delSpeed;
			enemyShotSize += delSize;
		}

		/*�����蔻��*/
		///�G�l�~�[�̒e�ƃv���C���[�̓����蔻��
		//�����̌v�Z
		int delX = pPlayer->X - pEBullet->X;//x�̑��΋���
		int delY = pPlayer->Y - pEBullet->Y;//y�̑��΋���
		int magLen = delX * delX + delY * delY;//�����̃}�O�j�`���[�h(2��)
		int delR = pPlayer->getR() + pEBullet->getR();//������������R
		int magR = delR * delR;//R�̃}�O�j�`���[�h(2��)
		//�����蔻��̌v�Z
		if (magLen < magR)
		{
			//�������Ă���debugNum�ύX
			debugNum = 1;
		}
		else
		{
			debugNum = 0;
		}
		///�G�l�~�[��Player�̒e�̓����蔻��
		for (int i = 0; i < PLAYER_SHOT_MAX; i++)
		{
			//�����̌v�Z
			delX = pEnemy->X - pPBullet[i]->X;//x�̑��΋���
			delY = pEnemy->Y - pPBullet[i]->Y;;//y�̑��΋���
			magLen = delX * delX + delY * delY;//�����̃}�O�j�`���[�h(2��)
			delR = pEnemy->getR() + pPBullet[i]->getR();//������������R
			magR = delR * delR;//R�̃}�O�j�`���[�h(2��)
			//�����蔻��̌v�Z
			if (magLen < magR)
			{
				//�������Ă���G�l�~�[�̐F�ς���
				pEnemy->setColor(ColorCode::YELLOW);
				break;//�ꔭ�ł��������Ă��瓖�����Ă������B
			}
			else
			{
				pEnemy->setColor(ColorCode::AQUA);
			}
		}

		/*Draw*/
		//player.
		pPlayer->Draw();
		//enemy.
		pEnemy->Draw();
		//eBullet.
		pEBullet->Draw();
		//pBullet.
		for (int i = 0; i < PLAYER_SHOT_MAX; i++)
		{
			pPBullet[i]->Draw();
		}

		/*DebguDraw*/
		//Debu����
		DrawFormatString(0, 0, ColorCode::RED, "WSAD(�㉺���E),Enter(�V���b�g)");
		DrawFormatString(0, 20, ColorCode::RED, "debugNum:%d", debugNum);
		//�R���W�����\��
		pPlayer->DebugDraw();
		pEnemy->DebugDraw();

		//����ʂ�\��
		ScreenFlip();
		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }
		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }
		//fps�Œ�(60fps:16.66ms)
		//���[�v�J�n��������16.66ms�o�܂Œ�~
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}
