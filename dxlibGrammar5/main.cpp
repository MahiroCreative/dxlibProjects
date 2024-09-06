#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//���������e�͕K�v�Œ���ł��B�������o�܂��B�܂��ڍׂȉ�������Ă��܂���B
//�������t�@�����X��O���T�C�g���Q�l�ɂ��Ă��������B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�E�Q�[���v���O���~���O
// �@- Input����(Key���͂̊g��)
// �@- Draw(),DebgugDraw()�̔ėp�������߂�B
//�EC/C++����
//   - �\���̂Ń|�����[�t�B�Y�����ǂ�

/*�\���̂̍쐬*/
//�S�ẴI�u�W�F�N�g����̍\���̂ō�邱�ƂŁA
//�֐��ɓn�����������炵����A�Ԃ�l�Ŏ󂯎��₷��������A�f�[�^�̂�����P��������B
//GameOject.
struct GameObject
{
	//�S�ẴI�u�W�F�N�g�ɑΉ��ł���悤�ɕϐ����R�p��(�Ƃ肠�����S��NULL�ŏ�����)
	int DrawHandle = NULL;//�摜�n���h��
	int X = NULL;//X���W
	int Y = NULL;//Y���W
	int R = NULL;//���a
	int Speed = NULL;//���x
	int MaxShotNum = NULL;//���˂ł���ő�e��
	int ShotCount = NULL;//���ݔ��˂��Ă���e��
	unsigned int Color = NULL;//�F
	unsigned int HitColor = NULL;//Hit�F
	double Scale = NULL;//�X�P�[��
	double Rotate = NULL;//��]�x
	bool IsHit = NULL;//�����蔻��
	bool IsVisible = NULL;//�\������Ă��邩
};
//KeyInput.(Key�����݉�����Ă��邩�Ȃǂ�ۑ����Ă���)
struct IsKeyInput
{
	bool IsNow = false;//�����ꂽ�u��True
	bool IsHold = false;//������Ă���Œ�True
};

/*�v���g�^�C�v�錾*/
bool IsHitCollision(GameObject _hitObj, GameObject _bullets[], int MAX);//�������Ƒ������̓����蔻��.��O�����͔z��̍ő吔
IsKeyInput InputKeyUpdate(IsKeyInput _keyFlag);//�������ŃL�[�t���O��n���A�X�V�������œ���
void Draw(GameObject _gameObjects[], int _objNum);//��ʕ\��
void DebugDraw(GameObject _gameObjects[], int _objNum);//Debug�\��

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�Q�[�����[�v�p�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�Q�[���p�萔*/
	constexpr int MAX_SHOT_NUM = 3;
	constexpr int MAX_GAMEOBJ_NUM = MAX_SHOT_NUM * 2 + 2;

	/*�Q�[���p�ϐ�*/
	//InputKey.
	IsKeyInput IsKeyFlag;
	//Player.
	GameObject Player;
	Player.DrawHandle = LoadGraph("Chara.png");
	Player.X = 100;
	Player.Y = 300;
	Player.R = 12;
	Player.Scale = 1;
	Player.MaxShotNum = MAX_SHOT_NUM;
	Player.ShotCount = 0;
	Player.Rotate = 0;
	Player.Speed = 4;
	Player.IsHit = false;
	Player.IsVisible = true;
	//Enemy.
	GameObject Enemy;
	Enemy.X = 1000;
	Enemy.Y = 360;
	Enemy.R = 80;
	Enemy.Speed = 1;
	Enemy.MaxShotNum = MAX_SHOT_NUM;
	Enemy.ShotCount = 0;
	Enemy.Color = GetColor(255, 0, 255);
	Enemy.HitColor = GetColor(0, 0, 255);
	Enemy.IsHit = false;
	Enemy.IsVisible = true;
	//PlayerBullet.
	GameObject pBullet[MAX_SHOT_NUM];
	for (int i = 0; i < MAX_SHOT_NUM; i++)//������
	{
		pBullet[i].X = Player.X;
		pBullet[i].Y = Player.Y;
		pBullet[i].R = 4;
		pBullet[i].Speed = 8;
		pBullet[i].Color = GetColor(255, 255, 255);
		pBullet[i].IsVisible = false;
	}
	//EnemyBullet.
	GameObject eBullet[MAX_SHOT_NUM];
	for (int i = 0; i < MAX_SHOT_NUM; i++)//������
	{
		eBullet[i].X = Enemy.X;
		eBullet[i].Y = Enemy.Y;
		eBullet[i].R = 32;
		eBullet[i].Speed = 8;
		eBullet[i].Color = GetColor(0, 255, 0);
		eBullet[i].IsVisible = false;
	}
	//DrawOjects.
	GameObject drawObjects[MAX_GAMEOBJ_NUM];

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*Key���͂̍X�V*/
		IsKeyFlag = InputKeyUpdate(IsKeyFlag);

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
		if (IsKeyFlag.IsNow && Player.ShotCount < Player.MaxShotNum)
		{
			//���݌����Ă��鋅���̍X�V
			Player.ShotCount++;
			for (int i=0;i<Player.ShotCount;i++)
			{
				pBullet[i].IsVisible = true;
			}
		}

		/*PlayerBullet�̏���*/
		for (int i = 0; i < Player.MaxShotNum; i++)
		{
			if (pBullet[i].IsVisible && pBullet[i].X > 1280)//��ʊO�ɏo���Ȃ珉����
			{
				//������
				pBullet[i].X = Player.X;
				pBullet[i].Y = Player.Y;
				pBullet[i].IsVisible = false;
				//���������ꂽ�����������Ă��鋅�������炷
				Player.ShotCount--;
			}
			else if (pBullet[i].IsVisible)//��ʓ��Ȃ�ړ�
			{
				//�ړ�����
				pBullet[i].X += pBullet[i].Speed;
			}
			else//�����ĂȂ���Ԃł��v���C���[�ɒǐ�
			{
				pBullet[i].X = Player.X;
				pBullet[i].Y = Player.Y;
			}
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
				eBullet[Enemy.ShotCount].IsVisible = true;
				Enemy.ShotCount++;
			}
		}

		/*EnemyBullet�̏���*/
		for (int i = 0; i < Enemy.MaxShotNum; i++)
		{
			if (eBullet[i].IsVisible && eBullet[i].X < 0)//��ʊO�ɏo���Ȃ珉����
			{
				//������
				eBullet[i].X = Enemy.X;
				eBullet[i].Y = Enemy.Y;
				eBullet[i].IsVisible = false;
				//�����Ă���e�ې���������
				Enemy.ShotCount = 0;
			}
			else if (eBullet[i].IsVisible)//��ʓ��Ȃ�ړ�
			{
				//�ړ�����
				eBullet[i].X -= eBullet[i].Speed;
			}
			else//�����ĂȂ���Ԃł��G�l�~�[�ɒǐ�
			{
				eBullet[i].X = Enemy.X;
				eBullet[i].Y = Enemy.Y;
			}
		}

		/*�����蔻��*/
		Player.IsHit = IsHitCollision(Player, eBullet, MAX_SHOT_NUM);//Player�̓����蔻��
		Enemy.IsHit = IsHitCollision(Enemy, pBullet, MAX_SHOT_NUM);//Enemy�̓����蔻��

		/*GameObject����̔z��ɂ���*/
		//Player�̑}��
		drawObjects[0] = Player;
		//Enemy�̑}��
		drawObjects[1] = Enemy;
		//PlayerBullet�̑}��
		for (int i = 0; i < MAX_SHOT_NUM; i++)
		{
			drawObjects[i + 2] = pBullet[i];
		}
		//EnemyBullet�̑}��
		for (int i = 0; i < MAX_SHOT_NUM; i++)
		{
			drawObjects[i + 2 + MAX_SHOT_NUM] = eBullet[i];
		}

		/*Draw*/
		Draw(drawObjects, MAX_GAMEOBJ_NUM);

		/*DebugDraw*/
		DebugDraw(drawObjects, MAX_GAMEOBJ_NUM);

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


/*�֐�*/
//���L�̂悤�ȏ������ŁA�����ɂ��R�����g���t����܂��B

/// <summary>
/// �L�[�̏�Ԃ����擾.�����ꂽ�u�Ԃ��A�܂��͉����ꑱ���Ă���̂����Ԃ����B
/// ChceckHitKey()�ł͉�����Ă���Ԃ������Ɣ�������̂ŁA�������u�Ԃ��擾�ł��Ȃ�(��񂾂�����������ł�10�񂭂炢�����ꂽ�����ɂȂ�)�B
/// ���̂��߁A���̊֐��Łw�����ꂽ�u�ԁx���擾����B����̓v���C���[�̒e�̔��˂Ŏg�p����B
/// �������ŃL�[�t���O��n���A�X�V�������œ���.
/// �Q�[�����[�v���ɖ��t���[�����s���邱�ƂŊm�F���Ă���B
/// ����̓G���^�[�������`�F�b�N���Ă���B
/// </summary>
/// <param name="_keyFlag">���g�ō쐬�����L�[�t���O</param>
/// <returns></returns>
IsKeyInput InputKeyUpdate(IsKeyInput _keyFlag)
{
	IsKeyInput ans;

	//EnterKey.
	if (CheckHitKey(KEY_INPUT_RETURN) && !_keyFlag.IsHold)//�G���^�[��������A�����ꑱ���Ă��Ȃ��B
	{
		//�����ꂽ�u��
		ans.IsNow = true;
		ans.IsHold = true;
	}
	else if (CheckHitKey(KEY_INPUT_RETURN) && _keyFlag.IsHold)//�G���^�[��������A�����ꑱ���Ă���.
	{
		//�����ꑱ���Ă���
		ans.IsNow = false;
		ans.IsHold = true;
	}
	else//Enter��������Ă��Ȃ��B
	{
		ans.IsNow = false;
		ans.IsHold = false;
	}

	return ans;
}

/// <summary>
/// �������Ƒ������̓����蔻��
/// </summary>
/// <param name="_hitObj"></param>
/// <param name="_bullets"></param>
/// <returns></returns>
bool IsHitCollision(GameObject _hitObj, GameObject _bullets[], int MAX)
{
	int delX;//X�����̋���
	int delY;//Y�����̋���
	int delR;//���a�̍��v

	for (int i = 0; i < MAX; i++)
	{
		//�v�Z
		delX = _hitObj.X - _bullets[i].X;
		delY = _hitObj.Y - _bullets[i].Y;
		delR = _hitObj.R + _bullets[i].R;
		//����
		if ((delX * delX + delY * delY) < (delR * delR))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐��B
/// </summary>
/// <param name="_gameObjects">�S�I�u�W�F�N�g�̔z��</param>
/// <param name="_objNum">�Q�[���I�u�W�F�N�g�̑���</param>
void Draw(GameObject _gameObjects[], int _objNum)
{
	for (int i = 0; i < _objNum; i++)
	{
		if ((_gameObjects[i].DrawHandle != NULL) && _gameObjects[i].IsVisible)//�摜�n���h���L��
		{
			//Plyer�̕`��
			DrawRotaGraph(_gameObjects[i].X, _gameObjects[i].Y, _gameObjects[i].Scale, _gameObjects[i].Rotate, _gameObjects[i].DrawHandle, 1);
		}
		else if (_gameObjects[i].IsVisible)//�摜�n���h������
		{
			//Plyer�ȊO�̕`��
			if (_gameObjects[i].IsHit)//�����������B
			{
				DrawCircle(_gameObjects[i].X, _gameObjects[i].Y, _gameObjects[i].R, _gameObjects[i].HitColor);
			}
			else
			{
				DrawCircle(_gameObjects[i].X, _gameObjects[i].Y, _gameObjects[i].R, _gameObjects[i].Color);
			}

		}
	}
}

/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐�(Debug�p)�B
/// </summary>
/// <param name="_gameObjects">�I�u�W�F�N�g�S�Ă̔z��</param>
/// <param name="_objNum">�Q�[���I�u�W�F�N�g�̑���</param>
void DebugDraw(GameObject _gameObjects[], int _objNum)
{
	//�I�u�W�F�N�g��
	for (int i = 0; i < _objNum; i++)
	{
		if (_gameObjects[i].IsVisible)
		{
			DrawCircle(_gameObjects[i].X, _gameObjects[i].Y, _gameObjects[i].R, GetColor(255, 0, 0), 0);
		}

		/*�f�o�b�O�e�L�X�g*/
		if ((_gameObjects[i].DrawHandle != NULL) && _gameObjects[i].IsVisible)//�摜�n���h���L��(Player)
		{
			//Plyer�̕`��
			DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerHit:%d", _gameObjects[i].IsHit);
		}
	}

	/*�������*/
	DrawString(0, 0, "�������:WASD(�㍶���E),Enter(����)", GetColor(255, 0, 0));


}