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
	bool IsShot = NULL;//�e�������Ă��邩
	bool IsHit = NULL;
	bool IsVisible = NULL;
};


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

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/


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