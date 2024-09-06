#include "DxLib.h"

/*�T�v*/
//���́wGrammer�V���[�Y�x�ł�DxLib��Q�[���v���O���~���O�̊�b�I�Ȏg�����ƍl������i�K�I�ɂ��܂��B
//�������A���̃V���[�Y�ŉ��������e�͕K�v�K�v�A�Ƃ������x���ł��B�������o�܂��B
//Dxlib�̃��t�@�����X��p�ɂɌ��Ċ֐��ɈӖ��Ȃǂ��m�F���Ȃ���i�߂�̂��������g�����ł��B
//�y���t�@�����X�z
// https://dxlib.xsrv.jp/dxfunc.html

/*����̗v�f*/
//�EDxLib
// �@- 	DrawRotaGraph();
//�E�Q�[���v���O���~���O
//   - �~�̓����蔻��

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*Dxlib������*/
	SetGraphMode(1280, 720, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�摜�̓ǂݍ���*/
	int drawHandle = LoadGraph("Chara.png");

	/*�ϐ�*/
	//Player�ϐ�
	int pPosX = 100;//x���W
	int pPosY = 300;//y���W
	double pScale = 1;//�摜�̔{��
	double pRotate = 0;//��]�p�x(���W�A��)
	int pSpeed = 2;
	//Bullet�ϐ�
	int bPosX = pPosX;
	int bPosY = pPosY;
	int bR = 4;
	int bSpeed = 8;
	bool isBullet = false;
	//Enemy�ϐ�
	int ePosX = 1000;
	int ePosY = 360;
	int eR = 80;
	int eSpeed = 8;
	bool isHit = false;

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (TRUE)
	{
		//����ʂ̏�����
		ClearDrawScreen();

		/*Player����*/
		//�ړ�����
		if (CheckHitKey(KEY_INPUT_W))//W�ŏ�ړ�
		{
			pPosY -= pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_S))//S�ŉ��ړ�
		{
			pPosY += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_D))//D�ŉE�ړ�
		{
			pPosX += pSpeed;
		}
		else if (CheckHitKey(KEY_INPUT_A))//A�ō��ړ�
		{
			pPosX -= pSpeed;
		}
		//��]����
		if (CheckHitKey(KEY_INPUT_R))
		{
			pRotate += 0.1;
		}
		else if (pRotate > (3.14 *2))
		{
			pRotate = 0;
		}
		//�g�又��
		if (CheckHitKey(KEY_INPUT_Q))
		{
			pScale += 0.1f;
		}
		else//�ʓ|�Ȃ̂Ń{�^�������ĂȂ��Ƃ����߂�
		{
			pScale = 1;
		}

		/*Bullet����*/
		//�e�̔���
		if (CheckHitKey(KEY_INPUT_RETURN) && isBullet == false)//�e�͈ꔭ�������˂ł��Ȃ�
		{
			isBullet = true;
		}
		//�e�̈ړ�
		if (isBullet)
		{
			bPosX += bSpeed;
		}
		//�e�̈ʒu������
		if (bPosX > 1280)//��ʊO�ɏo����
		{
			bPosX = pPosX;
			bPosY = pPosY;
			isBullet = false;
		}

		/*Enemy����*/
		//�~�̓����蔻��
		//�w�e�̒��S����G�l�~�[�̒��S�܂ł̋����x<�w�e�̔��a + �G�l�~�[�̔��a�x�Ȃ�A�������Ă���ƌ�����B
		//�{���Ȃ� ��(�e�̍��W - �G�l�~�[�̍��W)^2 < �e�̔��a+�G�l�~�[�̔��a ���r���邱�ƂɂȂ邪�A
		//���[�g�̌v�Z�̓v���O���~���O�I�ɂ͏d���A�덷���o�₷���B�����ŗ��ӂ�2�悵�ĊȒP�ɂ���B
		//(�e�̍��W - �G�l�~�[�̍��W)^2 < (�e�̔��a+�G�l�~�[�̔��a)^2�@���r���邱�ƂŔ��肷��B
		//�O�����̒藝���A(�e�̍��W - �G�l�~�[�̍��W)^2 = (�e��x���W - �G�l�~�[��x���W)^2 + (�e��y���W - �G�l�~�[��y���W)^2
		int delBulletToEnemyX = bPosX - ePosX;//X�̍��W�̍�
		int delBulletToEnemyY = bPosY - ePosY;//Y�̍��W�̍�
		int delBulletToEnemyMag = delBulletToEnemyX * delBulletToEnemyX + delBulletToEnemyY * delBulletToEnemyY;
		int delRMag = (bR + eR) * (bR + eR);
		//�����蔻��̌v�Z
		if (delBulletToEnemyMag < delRMag)
		{
			isHit = true;
		}
		else
		{
			isHit = false;
		}


		/*Draw*/
		//�L�����N�^�`��
		//�O��܂Ŏg���Ă���DrawGraph���Ǝw����W���ǂݍ��񂾉摜�̍���ɂȂ��Ă��܂��B
		//�����h�����߂ɐ^�񒆂�\�����邱������g�p
		//������̊֐��͊g�嗦�Ɖ�]�p�x�Ȃǂ��w��ł���B
		DrawRotaGraph(pPosX,pPosY,pScale,pRotate,drawHandle,1);
		//�e�̕`��
		if (isBullet)
		{
			DrawCircle(bPosX, bPosY, bR, GetColor(255, 255, 255), 1);
		}
		//�G�l�~�[�`��
		if (isHit)//�e���������Ă�����F���ς��
		{
			DrawCircle(ePosX, ePosY, eR, GetColor(0, 0, 255), 1);
		}
		else
		{
			DrawCircle(ePosX, ePosY, eR, GetColor(255, 0, 255), 1);
		}



		/*DebugDraw*/
		DrawString(0,0,"�������:WASD(�㍶���E),R(��]),Q(�g��),Enter(����)",GetColor(255,0,0));



		//����ʂ�\��
		ScreenFlip();

		//����ʂ�\��(�_�u���o�b�t�@�����O3)
		ScreenFlip();
		/*���t���b�V������(-1�Ȃ�G���[)*/
		if (ProcessMessage() < 0) { break; }
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}