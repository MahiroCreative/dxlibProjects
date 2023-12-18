#include "DxLib.h"
#include "Game8.h"
#include "Player8.h"
#include "Shot8.h"
#include "Enemy8.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Dxlib������*/
	SetGraphMode(SCREEN_W, SCREEN_H, 32);//�𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	// �w�i�̃X�N���[�������邽�߂Ƀe�N�X�`�����[�h�����b�s���O�ɏC��.
	SetTextureAddressMode(DX_TEXADDRESS_WRAP);//(�B���֐�.�^�C�����ׂ��o����悤��)
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

	/*�Q�[���I�u�W�F�N�g�̍쐬*/
	Player player;
	Enemy enemy;
	Shot shot[SHOT];

	/*������*/
	player.Init();
	enemy.Init();
	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Init();
	}

	// �Q�[�����[�v.
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		// �e�A�b�v�f�[�g�֐����Ă�.
		player.Update(shot, SHOT);
		enemy.Update();
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Update(enemy);
		}

		// �e�`��֐����Ă�.
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Draw();
		}
		player.Draw();
		enemy.Draw();

		// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0)
		{
			break;
		}
		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}