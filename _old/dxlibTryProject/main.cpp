#include "DxLib.h"


//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*�萔*/
	//��ʃT�C�Y
	constexpr int ScreenSizeX = 1280;//��
	constexpr int ScreenSizeY = 720;//����

	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*�J�����ݒ�*/
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);
	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));


	/*���f���Ǎ���*/
	int modelHandle;
	modelHandle = MV1LoadModel("data/model/player/hackadoll.pmx");

	/*�Q�[���ϐ�*/
	VECTOR pos;
	pos = VGet(0,0,0);

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		/*�Q�[��������*/
		//���f������
		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		// ��������Ă������ɐi��
		if (key & PAD_INPUT_UP)
		{
			pos.z += 1;
		}
		// ���������Ă����牺�ɐi��
		if (key & PAD_INPUT_DOWN)
		{
			pos.z -= 1;
		}
		// �E�������Ă�����E�ɐi��
		if (key & PAD_INPUT_RIGHT)
		{
			pos.x += 1;
		}
		// ���������Ă����獶�ɐi��
		if (key & PAD_INPUT_LEFT)
		{
			pos.x -= 1;
		}
		//���f���ʒu�X�V
		MV1SetPosition(modelHandle, pos);

		/*�`��*/
		//����ʂ̏�����
		ClearDrawScreen();
		//���f���`��
		MV1DrawModel(modelHandle);
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
	DxLib::DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}
