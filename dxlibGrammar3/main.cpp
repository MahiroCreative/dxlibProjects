#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//���������e�͕K�v�Œ���ł��B�������o�܂��B�܂��ڍׂȉ�������Ă��܂���B
//�������t�@�����X��O���T�C�g���Q�l�ɂ��Ă��������B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
//   - ���Ԃ̑���
// �@- fps�̌Œ�
//�E�Q�[���v���O���~���O
//   - fps�̌Œ�
//�EC/C++����
//   - �\����

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�\���̂̍쐬*/
	//�Q�[���I�u�W�F�N�g�p�̍\����
	//�\���͕̂ϐ����P�ɂ܂Ƃ߂��BPlayer��G�l�~�[�ȂǊ֘A����ϐ����P�ɂ܂Ƃ߂Ă������B
	//Player.
	struct Player
	{
		int drawHandle;//�摜�n���h��
		int posX;//X���W
		int posY;//Y���W
		int R;//���a
		int speed;//���x
		double scale;//�X�P�[��
		double rotate;//��]�x
	};
	//Enemy.
	struct Enemy
	{
		int posX;//X���W
		int posY;//Y���W
		int R;//���a
		int speed;//���x
		unsigned int color;//�F.iroGetColor�œ�����̂�unsigned int �Ȃ̂ŁB
		unsigned int hitColor;//�e�������������̐F
	};
	//Bullet.
	struct Bullet
	{
		int posX;//X���W
		int posY;//Y���W
		int R;//���a
		int speed;//���x
		unsigned int color;//�F.
	};

	/*�ϐ�*/
	//Player.
	Player Player;
	Player.drawHandle = LoadGraph("Chara.png");
	Player.posX = 100;//x���W
	Player.posY = 300;//y���W
	Player.R = 2;//���a
	Player.speed = 2;//�X�s�[�h
	Player.scale = 1;//�X�P�[��
	Player.rotate = 0;//��]�x
	//Enemy.
	Enemy Enemy;
	Enemy.posX = 1000;
	Enemy.posY = 360;
	Enemy.R = 80;
	Enemy.speed = 1;
	Enemy.color = GetColor(255, 0, 255);
	Enemy.hitColor = GetColor(0, 0, 255);
	//PlayerBullet.
	Bullet pBullet;
	pBullet.posX = Player.posX;
	pBullet.posY = Player.posY;
	pBullet.R = 4;
	pBullet.speed = 8;
	pBullet.color = GetColor(255, 255, 255);
	//EnemyBullet.
	Bullet eBullet;
	eBullet.posX = Enemy.posX;
	eBullet.posY = Enemy.posY;
	eBullet.R = 32;
	eBullet.speed = 4;
	eBullet.color = GetColor(0, 255, 0);
	//�t���O�p�ϐ�
	bool isPlayerBullet = false;
	bool isEnemyBullet = false;
	bool isEnemyHit = false;
	bool isPlayerHit = false;

	/*�Q�[�����[�v��*/
	//gameRoop.
	//���[�v�̍ŏ��ƍŌ�ɒ��ڂ��ė~�����B
	//���ꂼ��GetNowHiPerformanceCount()�Ō��݂̎������擾���Ă���B
	//�������Ă��邩�Ƃ����ƁA���[�v�̊J�n���̎������烋�[�v�I�����̎����������Ă���B
	//���̒l��16.66ms�ɂȂ�܂Ŏ��̃��[�v�ɍs���Ȃ��悤�ɂ��Ă���B
	//�������邱�ƂŁA1�b�ԂɃ��[�v�������邩�𐧌��ł���B�����60fps�ɂ��Ă���B
	//���̂悤�ɐ������邱�ƂŃQ�[���̓�������̊Ԋu�ɕۂ��Ƃ��ł��A�����郉�O�Ƃ������̂̔��������点��B
	//(���O��܂ł̃R�[�h���ƒe�̔��ˈʒu�����܂ɃY���Ă������ł��B)
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*Player����*/
		//�ړ�����
		if (CheckHitKey(KEY_INPUT_W))//W�ŏ�ړ�
		{
			Player.posY -= Player.speed;
		}
		else if (CheckHitKey(KEY_INPUT_S))//S�ŉ��ړ�
		{
			Player.posY += Player.speed;
		}
		else if (CheckHitKey(KEY_INPUT_D))//D�ŉE�ړ�
		{
			Player.posX += Player.speed;
		}
		else if (CheckHitKey(KEY_INPUT_A))//A�ō��ړ�
		{
			Player.posX -= Player.speed;
		}
		//�e�̔���
		if (CheckHitKey(KEY_INPUT_RETURN) && !isPlayerBullet)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			isPlayerBullet = true;
		}

		/*Enemy����*/
		//�ړ�����
		Enemy.posY += Enemy.speed;
		if (Enemy.posY > 640 || Enemy.posY < 80)//�㉺�^���������Ă���B
		{
			Enemy.speed = -Enemy.speed;
		}
		//�e�̔���
		if (!isEnemyBullet)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			isEnemyBullet = true;
			eBullet.speed += 1;//�G�l�~�[�̒e�̑��x�������тɑ�������
		}

		/*PlayerBullet����*/
		if (isPlayerBullet && pBullet.posX < 1280)//�e�����˂���Ă���A��ʓ��Ȃ�ړ�
		{
			pBullet.posX += pBullet.speed;
		}
		else//��ʊO�Ȃ珉����
		{
			pBullet.posX = Player.posX;
			pBullet.posY = Player.posY;
			isPlayerBullet = false;
		}

		/*EnemyBullet����*/
		if (isEnemyBullet)
		{
			eBullet.posX -= eBullet.speed;//�ړ�����
			//�ʒu�̏�����
			if (eBullet.posX < 0)
			{
				eBullet.posX = Enemy.posX;
				eBullet.posY = Enemy.posY;
				isEnemyBullet = false;
			}
		}

		/*�����蔻��*/
		//Player�̓����蔻��.
		int delX = Player.posX - eBullet.posX;//x�����̑��΍��W
		int delY = Player.posY - eBullet.posY;//y�����̑��΍��W
		int delR = Player.R + eBullet.R;//���ꂼ��̔��a�𑫂�
		//�~�̓����蔻��
		// ���݂��̒��S�������A���݂��̔��a�𑫂���������菬�����Ȃ��Ă���Γ������Ă���B
		// �O�����̒藝��������O���Ĉȉ��̎������B
		if ((delX*delX + delY*delY) < (delR*delR))
		{
			isPlayerHit = true;
		}
		else
		{
			isPlayerHit = false;
		}
		//Enemy�̓����蔻��
		delX = Enemy.posX - pBullet.posX;
		delY = Enemy.posY - pBullet.posY;
		delR = Enemy.R + pBullet.R;
		if ((delX * delX + delY * delY) < (delR * delR))
		{
			isEnemyHit = true;
		}
		else
		{
			isEnemyHit = false;
		}


		/*Draw*/
		//Player.
		DrawRotaGraph(Player.posX, Player.posY, Player.scale, Player.rotate, Player.drawHandle, 1);
		//PlayerBullet.
		if (isPlayerBullet)
		{
			DrawCircle(pBullet.posX, pBullet.posY, pBullet.R, pBullet.color, 1);
		}
		//Enemy.
		if (isEnemyHit)
		{
			DrawCircle(Enemy.posX, Enemy.posY, Enemy.R, Enemy.hitColor, 1);
		}
		else
		{
			DrawCircle(Enemy.posX, Enemy.posY, Enemy.R, Enemy.color, 1);
		}
		//EnemyBullet.
		if (isEnemyBullet)
		{
			DrawCircle(eBullet.posX, eBullet.posY, eBullet.R, eBullet.color, 1);
		}


		/*DebugDraw*/
		DrawString(0, 0, "�������:WASD(�㍶���E),Enter(����)", GetColor(255, 0, 0));
		DrawFormatString(0,20, GetColor(255, 0, 0),"Player�̓����蔻��:%d", isPlayerHit);

		//����ʂ�\��
		ScreenFlip();

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }

		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }//esc�ŋ����I��

		//fps�Œ�(60fps:16.66ms)
		//���[�v�J�n��������16.66ms�o�܂Œ�~
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}