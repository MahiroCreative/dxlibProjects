#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//���������e�͕K�v�Œ���ł��B�������o�܂��B�܂��ڍׂȉ�������Ă��܂���B
//�������t�@�����X��O���T�C�g���Q�l�ɂ��Ă��������B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�E�Q�[���v���O���~���O
// �@- �����I�u�W�F�N�g�̐���
//   - �ގ������̊֐���
//   - �R���W�����̃f�o�b�O�\��
//�EC/C++����
//   - �O���[�o���ϐ�
//   - �\���̂̏�����
// �@- �萔(constexpr)
// �@- Roop��(for��)
//   - �z��
//   - �֐�

/*�\���̂̍쐬(�O���[�o���ϐ��Ƃ��č\���̂��쐬)*/
//�\���̂��O���[�o���ϐ��Ƃ��č쐬����BMain�̊O�ɋL�q����΂悢�B
//�O���[�o���ϐ��Ƃ��č쐬���邱�ƂŁAMain�ȊO�̃��\�b�h�ł��g�p���邱�Ƃ��ł���B
//�܂��A�쐬���_�ŏ��������Ă������Ƃ��\.
//Player.
struct Player
{
	int DrawHandle = LoadGraph("Chara.png");//�摜�n���h��
	int X = 100;//X���W
	int Y = 300;//Y���W
	int R = 12;//���a
	double Scale = 1;//�X�P�[��
	double Rotate = 0;//��]�x
	int Speed = 4;//���x
	bool IsShot = false;//���ݒe�𔭎˂��Ă��邩
	bool IsHit = false;//�����蔻��p�̃t���O
};
//Enemy.
struct Enemy
{
	int X = 1000;//X���W
	int Y = 360;//Y���W
	int R = 80;//���a
	int Speed = 1;//���x
	int MaxShotNum = NULL;//���˂ł���ő�e�ې�
	int ShotCount = 0;//���ݔ��˂��Ă���e�ې�
	unsigned int Color = GetColor(255, 0, 255);
	unsigned int hitColor = GetColor(0, 0, 255);
	bool IsHit = false;//�����蔻��p�̃t���O
};
//Bullet.
struct Bullet
{
	int X = NULL;//X���W
	int Y = NULL;//Y���W
	int R = NULL;//���a
	int Speed = NULL;//���x
	unsigned int Color = NULL;//���x
	bool IsVisible = false;
};

/*�֐�*/
//�ގ��@�\�͊֐��Ƃ��Ă܂Ƃ߂Ă��܂��B
//�v���g�^�C�v�錾���Ă������ƂŁA�ォ�珈�����L�q���Ă��g����悤�ɂȂ�B
//�v���g�^�C�v�錾.
bool IsHitPlayerCollision(Player _hitObj, Bullet _eBullets[], int _MAXSHOT);//Player�ƃG�l�~�[�̒e�������������𔻒�
bool IsHitEnemyCollision(Enemy _hitObj, Bullet _pBullet);//�G�l�~�[�ƃv���C���[�̒e�������������𔻒�
void Draw(Player _player, Enemy _enemy, Bullet _pBullet, Bullet _eBullets[]);//��ʕ\��
void DebugDraw(Player _player, Enemy _enemy, Bullet _pBullet, Bullet _eBullets[]);//Debug�\��

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	/*�萔*/
	//�v���O�����̎��s��ɕύX����\�����������l�́A�萔�Ƃ��Ċm�ۂ��ׂ��ł���B
	// �萔�̍����́A�w#define�x��wconst�x�ȂǐF�X���邪�A
	// �P�Ȃ�萔�Ƃ��Ĉ����Ȃ�wconstexpr�x����Ԗ����N�����Ȃ��\���������B
	// ���̑��̒萔�͕K�v�ɂȂ����ۂɊw�K���Ďg�p����΂悢�B
	//��ʃT�C�Y(�萔).
	constexpr int SCREEN_SIZE_X = 1280;//��
	constexpr int SCREEN_SIZE_Y = 720;//����
	//�G�l�~�[�̍ő�e�ې�
	constexpr int MAX_ENEMY_SHOT = 3;

	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�ϐ�*/
	//Player.
	Player Player;
	//Enemy.
	Enemy Enemy;
	Enemy.MaxShotNum = MAX_ENEMY_SHOT;
	//PlayerBullet.
	Bullet pBullet;
	pBullet.X = Player.X;
	pBullet.Y = Player.Y;
	pBullet.R = 4;
	pBullet.Speed = 8;
	pBullet.Color = GetColor(255, 255, 255);
	//EnemyBullet.
	//�������̂���C�Ɉ����Ȃ�z��
	Bullet eBullets[MAX_ENEMY_SHOT];

	/*EnemyBullet�̏���������*/
	//�z��ɂ��Ă����΁A���[�v���Ȃǂň�C�ɏ������\
	// (if���ȂǂƘA�g����Ώ����ɉ����Ēl���ύX�ł���)
	for (int i = 0; i < MAX_ENEMY_SHOT; i++)
	{
		eBullets[i].X = Enemy.X;
		eBullets[i].Y = Enemy.Y;
		eBullets[i].R = 32;
		eBullets[i].Speed = 8;
		eBullets[i].Color = GetColor(0, 255, 0);
	}

	/*�Q�[�����[�v��*/
	//gameRoop.
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
			Player.Y -= Player.Speed;
		}
		else if (CheckHitKey(KEY_INPUT_S))//S�ŉ��ړ�
		{
			Player.Y += Player.Speed;
		}
		else if (CheckHitKey(KEY_INPUT_D))//D�ŉE�ړ�
		{
			Player.X += Player.Speed;
		}
		else if (CheckHitKey(KEY_INPUT_A))//A�ō��ړ�
		{
			Player.X -= Player.Speed;
		}
		//�e�̔���
		if (CheckHitKey(KEY_INPUT_RETURN) && !Player.IsShot)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			Player.IsShot = true;
		}

		/*Enemy����*/
		//�ړ�����
		Enemy.Y += Enemy.Speed;
		if (Enemy.Y > 640 || Enemy.Y < 60)//�㉺�^���������Ă���B
		{
			Enemy.Speed = -Enemy.Speed;
		}
		//�ϑ��I�ɔ���
		if (Enemy.ShotCount < Enemy.MaxShotNum)//�ő�ʐ��ɒB���Ă��Ȃ��B
		{
			if (Enemy.Y % 80 == 0)//���AY���W��80�Ŋ���؂��Ƃ�
			{
				eBullets[Enemy.ShotCount].IsVisible = true;
				Enemy.ShotCount++;
			}
		}

		/*PlayerBullet����*/
		if (Player.IsShot && pBullet.X < 1280)//�e�����˂���Ă���A��ʓ��Ȃ�ړ�
		{
			pBullet.X += pBullet.Speed;
		}
		else//��ʊO�Ȃ珉����
		{
			pBullet.X = Player.X;
			pBullet.Y = Player.Y;
			Player.IsShot = false;
		}

		/*EnemyBullet�̏���*/
		for (int i = 0; i < MAX_ENEMY_SHOT; i++)
		{
			if (eBullets[i].IsVisible && eBullets[i].X < 0)//��ʊO�ɏo���Ȃ珉����
			{
				//������
				eBullets[i].X = Enemy.X;
				eBullets[i].Y = Enemy.Y;
				eBullets[i].IsVisible = false;
				//�����Ă���e�ې���������
				Enemy.ShotCount = 0;
			}
			else if (eBullets[i].IsVisible)//��ʓ��Ȃ�ړ�
			{
				//�ړ�����
				eBullets[i].X -= eBullets[i].Speed;
			}
			else//�����ĂȂ���Ԃł��G�l�~�[�ɒǐ�
			{
				eBullets[i].X = Enemy.X;
				eBullets[i].Y = Enemy.Y;
			}
		}


		/*�����蔻��*/
		//Enemy�̓����蔻��.
		Enemy.IsHit = IsHitEnemyCollision(Enemy, pBullet);
		//Player�̓����蔻��
		Player.IsHit = IsHitPlayerCollision(Player, eBullets, MAX_ENEMY_SHOT);


		/*Draw*/
		Draw(Player, Enemy, pBullet, eBullets);

		/*DebugDraw*/
		DebugDraw(Player, Enemy, pBullet, eBullets);

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



/*�֐��̎���*/
//���L�̂悤�ȏ�����������ƁA�֐��Ƀ}�E�X�|�C���^���d�˂��ۂɃR�����g���Q�Ƃł���B

/// <summary>
/// Player�ƃG�l�~�[�̒e�������������𔻒�
/// </summary>
bool IsHitPlayerCollision(Player _hitObj, Bullet _eBullets[], int MAXSHOT)
{
	int delX;//X�����̋���
	int delY;//Y�����̋���
	int delR;//���a�̍��v

	for (int i=0; i < MAXSHOT; i++)
	{
		//�v�Z
		delX = _hitObj.X - _eBullets[i].X;
		delY = _hitObj.Y - _eBullets[i].Y;
		delR = _hitObj.R + _eBullets[i].R;
		//����
		if ((delX * delX + delY * delY) < (delR * delR))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �G�l�~�[�ƃv���C���[�̒e�������������𔻒�
/// </summary>
bool IsHitEnemyCollision(Enemy _hitObj, Bullet _pBullet)
{
	bool ans = false;
	int delX = _hitObj.X - _pBullet.X;//X�����̋���
	int delY = _hitObj.Y - _pBullet.Y;//Y�����̋���
	int delR = _hitObj.R + _pBullet.R;//���a�̍��v

	if ((delX * delX + delY * delY) < (delR * delR))
	{
		ans = true;
	}
	else
	{
		ans = false;
	}

	return ans;
}

/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐��B
/// </summary>
void Draw(Player _player, Enemy _enemy, Bullet _pBullet, Bullet _eBullets[])
{
	//Plyer�̕`��
	DrawRotaGraph(_player.X, _player.Y, _player.Scale, _player.Rotate, _player.DrawHandle, 1);
	//Enemy�̕`��
	if (_enemy.IsHit)//�������Ă�Ƃ�
	{
		DrawCircle(_enemy.X, _enemy.Y, _enemy.R, _enemy.hitColor);
	}
	else//�������ĂȂ��Ƃ�
	{
		DrawCircle(_enemy.X, _enemy.Y, _enemy.R, _enemy.Color);
	}

	//PlayerBullet�̕`��
	if (_player.IsShot)
	{
		DrawCircle(_pBullet.X, _pBullet.Y, _pBullet.R, _pBullet.Color);
	}
	//EnemyBullet�̕`��
	for (int i = 0; i < _enemy.MaxShotNum; i++)
	{
		if (_eBullets[i].IsVisible)
		{
			DrawCircle(_eBullets[i].X, _eBullets[i].Y, _eBullets[i].R, _eBullets[i].Color, 1);
		}

	}
}

/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐�(Debug�p)�B
/// </summary>
void DebugDraw(Player _player, Enemy _enemy, Bullet _pBullet, Bullet _eBullets[])
{
	/*�������*/
	DrawString(0, 0, "�������:WASD(�㍶���E),Enter(����)", GetColor(255, 0, 0));
	/*�R���W�����\��*/
	//�R���W����(�����蔻��͈̔�)��\�����邱�ƂŃf�o�b�O���₭����B
	//Player.
	DrawCircle(_player.X, _player.Y, _player.R, GetColor(255, 0, 0), 0);
	//�f�o�b�O�e�L�X�g
	DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerHit:%d", _player.IsHit);
}