#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//�������A���̃V���[�Y�ŉ��������e�͕K�v�K�v�A�Ƃ������x���ł��B�������o�܂��B
//�܂��A���w�Ҍ����̉���̂悤�Ȏ��͂��Ă��܂���B�g�����̗Ⴊ�����Ă�����x�ł��B
//������Ȃ������͎���\���I�ɒ��ׂĉ������B
//Dxlib�̃��t�@�����X��p�ɂɌ��Ċ֐��ɈӖ��Ȃǂ��m�F���Ȃ���i�߂�̂��������g�����ł��B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
// �@�] Key����
//�EC���@
//   - if��


/*Dxlib�̃G���g���[�|�C���g*/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O


	/*�ϐ�*/
	//�v�Z�Ȃǂ�����ۂɈꎞ�I�l��ۑ����邽�߂Ɏg���B
	//�ǂ̂悤�Ȑ������������ɂ���Č^���ς��B
	//��{�I�ɂ͐�����int,������float�ƍl����Ƃ悢�B
	int drawHandle;//�����^
	int posX = 400;
	int moveX = 1;


	/*�摜�̓ǂݍ���*/
	//�������ɓǂݍ��݁A���̈ʒu�����Ă���B�����ŗ^����̂̓t�@�C���̃p�X�B
	//�������������摜�n���h���ƌ����B����̓v���W�F�N�g�t�H���_�����ɓ���Ă���B
	drawHandle = LoadGraph("Chara.png");


	/*�Q�[�����[�v��*/
	//��ʓI�ȃQ�[���͒P�ʎ��Ԗ��ɉ��x�����x���\�����J��Ԃ����ŕ\������܂��B
	//������Q�[�����[�v�ƌ����܂��B���ꂪ�ʏ�̃v���O���~���O�Ƃ̑傫�ȈႢ�ł��B
	//���[�U���������Ȃ��Ă����A���^�C���ŕ\�����ω�����̂��Q�[���Ȃ̂ŁA��΂ɕK�v�ȋ@�\�ƂȂ�܂��B
	//���ɉ����A�N�V������������Ζ����Ƀ��[�v����K�v�����邽�߁A�����ɂ�TRUE�����Ė������[�v���쐬���܂��B
	while (TRUE)
	{

		//����ʂ̏�����(�_�u���o�b�t�@�����O1)
		ClearDrawScreen();


		/*�Q�[��������(�_�u���o�b�t�@�����O2)*/
		//�~�̕\��
		DrawCircle(100, 100, 20, 200, 1, 1);//(x���W,y���W,���a,�F,�h��ׂ����ǂ���,�\�����邩)
		//���̕\��
		DrawLine(200, 200, 300, 300, 200, 1);//(�n�_x,�n�_y,�I�_x,�I�_y,�F,�\�����邩)
		//�摜�̕\��
		DrawGraph(posX, 400, drawHandle, 1);//(x���W,y���W,�ǂݍ��񂾉摜�̃n���h��,�\�����邩)

		//�摜�̈ړ�
		//���E�ɐU���^���������Ă���B
		posX += moveX;
		if (posX > 1200)
		{
			moveX = -moveX;
		}
		else if (posX < 100)
		{
			moveX = -moveX;
		}


		//����ʂ�\��(�_�u���o�b�t�@�����O3)
		ScreenFlip();


		/*���t���b�V������(-1�Ȃ�G���[)*/
		if (ProcessMessage() < 0) { break; }

	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}