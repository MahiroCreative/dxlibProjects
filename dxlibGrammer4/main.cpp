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
// �@- �萔(constexpr)
//   - �\���̕ϐ��̊ȒP�ȏ�����
// �@- Roop��(for��)
//   - �z��
//   - �֐�

/*�\���̂̍쐬(�O���[�o���ϐ��Ƃ��č\���̂��쐬)*/
//�\���̂��O���[�o���ϐ��Ƃ��č쐬����BMain�̊O�ɋL�q����΂悢�B
//�O���[�o���ϐ��Ƃ��č쐬���邱�ƂŁAMain�ȊO�̃��\�b�h�ł��g�p���邱�Ƃ��ł���B
//�܂��A�쐬���_�ŏ��������邱�Ƃ��\.(NULL�����Ă��邪�A�v�Z���0�Ƃ��Ďg���܂�)
struct GameObject
{
	int DrawHandle = NULL;//�摜�n���h��
	int X = NULL;//X���W
	int Y = NULL;//Y���W
	int R = NULL;//���a
	int Speed = NULL;//���x
	int ShotCount = NULL;//���ݔ��˂��Ă���e�̐�
	double Scale = NULL;//�X�P�[��
	double Rotate = NULL;//��]�x
	unsigned int Color = NULL;//�F
	unsigned int HitColor = NULL;//Hit���̐F
	bool IsHit = NULL;//�����蔻��p�̃t���O
};

/*�֐�*/
//�ގ��@�\�͊֐��Ƃ��Ă܂Ƃ߂Ă��܂��B
//�v���g�^�C�v�錾���Ă������ƂŁA�ォ�珈�����L�q���Ă��g����悤�ɂȂ�B
//�v���g�^�C�v�錾.
bool IsHitCollision(GameObject _hitObj, GameObject _Bullets[]);//�������Ƒ������Q�������������𔻒�
void Draw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[]);//��ʕ\��
void DebugDraw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[]);//Debug�\��


//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�萔*/
	//�v���O�����̎��s��ɕύX����\�����������l�́A�萔�Ƃ��Ċm�ۂ��ׂ��ł���B
	// �萔�̍����́A�w#define�x��wconst�x�ȂǐF�X���邪�A
	// �P�Ȃ�萔�Ƃ��Ĉ����Ȃ�wconstexpr�x����Ԗ����N�����Ȃ��\���������B
	// ���̑��̒萔�͕K�v�ɂȂ����ۂɊw�K���Ďg�p����΂悢�B
	//��ʃT�C�Y.
	constexpr int SCREEN_SIZE_X = 1280;//��
	constexpr int SCREEN_SIZE_Y = 720;//����
	//�e��
	constexpr int PLAYER_MAX_SHOT = 4;//�v���C���[�̍ő�e��
	constexpr int ENEMY_MAX_SHOT = 2;//Enemy�̍ő�e��

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
	GameObject Player;
	Player.DrawHandle = LoadGraph("Chara.png");
	Player.X = 100;//x���W
	Player.Y = 300;//y���W
	Player.R = 2;//���a
	Player.ShotCount = 0;//���ݔ��˂��Ă���e��
	Player.Speed = 2;//�X�s�[�h
	Player.Scale = 1;//�X�P�[��
	Player.Rotate = 0;//��]�x
	Player.HitColor = GetColor(255, 0, 0);//Hit�F
	Player.IsHit = false;//�����蔻��
	//PlayerBullet.
	GameObject pBullet[PLAYER_MAX_SHOT];
	//PlayerBullet�̏�����
	for (int i=0;i<PLAYER_MAX_SHOT;i++)
	{
		pBullet[i].X = Player.X;
		pBullet[i].Y = Player.Y;
		pBullet[i].R = 4;
		pBullet[i].Speed = 8;
		pBullet[i].Color = GetColor(255,255,255);
	}
	//Enemy.
	GameObject Enemy;
	Enemy.X = 1000;
	Enemy.Y = 360;
	Enemy.R = 80;
	Enemy.Speed = 1;
	Enemy.Color = GetColor(255, 0, 255);
	Enemy.HitColor = GetColor(0, 0, 255);
	Enemy.IsHit = false;
	//EnemyBullet.
	GameObject eBullet[ENEMY_MAX_SHOT];
	//PlayerBullet�̏�����
	for (int i = 0; i < ENEMY_MAX_SHOT; i++)
	{
		eBullet[i].X = Enemy.X;
		eBullet[i].Y = Enemy.Y;
		eBullet[i].R = 32;
		eBullet[i].Speed = 8;
		eBullet[i].Color = GetColor(255, 255, 255);
	}


	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/

		/*Draw*/
		Draw(Player,Enemy,pBullet,eBullet);

		/*DebugDraw*/
		DebugDraw(Player, Enemy, pBullet, eBullet);

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


/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐��B
/// </summary>
void Draw()
{

}
/// <summary>
/// Dxlib��p���ĉ�ʕ\�����s���֐�(Debug�p)�B
/// </summary>
void Draw(GameObject _player, GameObject _enemy, GameObject _pBullets[], GameObject _eBullets[])
{

}