#include "DxLib.h"

/*�T�v*/
//C����́w�֐��܂Łx�őg�񂾃V�[���Ǘ�(�V�[���}�l�[�W���[)
//������Ȃ��w����C�́w��b���@�x�𕜏K���Ă��������B

/*�\��*/
//���ꂼ��̃V�[�����֐�(���\�b�h)�Ƃ��ĕ������āA
//���s���郁�\�b�h��؂�ւ��鎖�ŃV�[���Ǘ������Ă���B

/*�O���[�o���ϐ�*/
//�萔
constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int GAMESCENE = 2;
//�ϐ�
bool isInputEnterHold = false;//InputEnter�p�̕ϐ�
bool isInputUpHold = false;//InputUp�p�̕ϐ�
bool isInputDownHold = false;//InputDown�p�̕ϐ�

/*�v���g�^�C�v�錾*/
//��`��Main�̉��B
int TitleScene();//�^�C�g���V�[��
int GameScene();//�Q�[���V�[��
bool InputEnter();//Enter�������ꂽ���ǂ����𔻒肷��֐�
bool InputUp();//Up�������ꂽ���ǂ����𔻒肷��֐�
bool InputDown();//Down�������ꂽ���ǂ����𔻒肷��֐�


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
	int nextScene = TITLESCENE;

	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
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
		//�V�[���Ǘ�
		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == GAMESCENE)
		{

			nextScene = GameScene();
		}
		else if (nextScene == GAMEEND)
		{
			break;
		}

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

/*�V�[����`*/
//�^�C�g����ʂ����s����V�[���B
//�Ԃ�l�Ŏ��Ɏ��s����V�[�����w�肷��B
int TitleScene()
{
	/*�ϐ�*/
	bool gameRoop = true;
	int nextScene = TITLESCENE;
	int arrowPosY = 440;

	/*�Q�[������*/
	while (gameRoop)
	{

		/*�v�Z����*/
		//Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}

			
		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//�^�C�g�����S
		SetFontSize(80);//�t�H���g�T�C�Y�㏸
		DrawString(460, 240, "DxlibGame", GetColor(255, 255, 255));
		SetFontSize(20);//�t�H���g�T�C�Y������

		//�Q�[���V�[���e�L�X�g
		DrawString(600, 440, "START", GetColor(255, 255, 255));

		//�Q�[���G���h�e�L�X�g
		DrawString(600, 480, "END", GetColor(255, 255, 255));

		//���
		DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));

		//DebugDraw����
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��

		//����ʂ�\��
		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			return GAMESCENE;
		}

	}

	//��O����
	return TITLESCENE;
}
//�Q�[����ʂ����s����V�[���B
//�Ԃ�l�Ŏ��Ɏ��s����V�[�����w�肷��B
int GameScene()
{
	/*�ϐ�*/
	bool gameRoop = true;
	int nextScene = GAMESCENE;

	/*�Q�[������*/
	while (gameRoop)
	{

		/*�v�Z����*/

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//DebugDraw����
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��

		//����ʂ�\��
		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			return TITLESCENE;
		}

	}

	//��O����
	return TITLESCENE;
}

/*Input�֐�*/
//Enter�������ꂽ���ǂ����𔻒肷��֐�
//Enter���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputEnter()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_RETURN) && !isInputEnterHold)
	{
		isInputEnterHold = true;
		return true;
	}
	else if(!CheckHitKey(KEY_INPUT_RETURN))
	{
		isInputEnterHold = false;
	}

	return false;
}
//Up�������ꂽ���ǂ����𔻒肷��֐�
//Up���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputUp()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_UP) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		isInputDownHold = false;
	}

	return false;
}
//Down�������ꂽ���ǂ����𔻒肷��֐�
//Down���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputDown()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_DOWN) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		isInputDownHold = false;
	}

	return false;
}