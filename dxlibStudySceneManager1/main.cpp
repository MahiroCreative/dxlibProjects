#include "DxLib.h"

/*�T�v*/
//C����̋@�\�݂̂őg�񂾃V�[���Ǘ�(�V�[���}�l�[�W���[)
//���̒��ł��֐��܂łőg��ł���B
//���̃��x����������Ȃ��w����C�̕��@�𕜏K���Ă��������B

/*�\��*/
//���ꂼ��̃V�[�����֐�(���\�b�h)�Ƃ��ĕ������āA
//���s���郁�\�b�h��؂�ւ��鎖�ŃV�[���Ǘ������Ă���B


//�v���g�^�C�v�錾
//��`��Main�̉��B
int TitleScene();
int GameScene();
bool InputKey(int KeyCode, int InputFrame);

/*�O���[�o���ϐ�*/
enum SceneKind//�V�[���Ǘ��p
{
	GAMEEND,
	TITLESCENE,
	GAMESCENE
};
int InputKeyTime = 0;//InputKey�p�̃O���[�o���ϐ�

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
	int nextScene = SceneKind::TITLESCENE;

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
		if (nextScene == SceneKind::TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == SceneKind::GAMESCENE)
		{
			nextScene = GameScene();
		}
		else if (nextScene == SceneKind::GAMEEND)
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
	/*�Q�[������*/


	/*Draw����*/
	//�^�C�g�����S
	SetFontSize(80);//�t�H���g�T�C�Y�㏸
	DrawString(460, 240, "DxlibGame", GetColor(255, 255, 255));
	SetFontSize(20);//�t�H���g�T�C�Y������



	/*DebugDraw����*/
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��


	/*�V�[���J�ڏ���*/
	//4�t���[���ȏ�Enter����������V�[���ύX
	if (InputKey(KEY_INPUT_RETURN, 4))
	{
		return SceneKind::GAMESCENE;
	}
	return SceneKind::TITLESCENE;
}
//�Q�[����ʂ����s����V�[���B
//�Ԃ�l�Ŏ��Ɏ��s����V�[�����w�肷��B
int GameScene()
{
	//�V�[�����̕\��
	SetFontSize(80);//�t�H���g�T�C�Y�㏸
	DrawString(420, 240, "GameScene", GetColor(255, 255, 255));
	SetFontSize(20);//�t�H���g�T�C�Y������

	//�V�[���ύX����
	//4�t���[���ȏ�Enter����������V�[���ύX
	if (InputKey(KEY_INPUT_RETURN,4))
	{
		return SceneKind::TITLESCENE;
	}

	return SceneKind::GAMESCENE;
}

/*�֐�*/
//Enter�������ꂽ���ǂ����𔻒肷��֐�
//�w�肵���t���[���ȏ㉟���ꂽ�牟���ꂽ�Ɣ��肷��B
//�������₷����D�悵���ꎞ�I�Ȃ��̂Ȃ̂ŁA���R�����蒼���Ă����܂��B
bool InputKey(int KeyCode,int InputFrame)
{
	//4�t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KeyCode) && InputKeyTime > InputFrame)
	{
		InputKeyTime = 0;
		return true;
	}
	else if (CheckHitKey(KeyCode))
	{
		InputKeyTime++;
	}

	return false;
}