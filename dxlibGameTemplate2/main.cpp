#include "DxLib.h"
#include <math.h>

/*�T�v*/
//����:DxlibGameTemplate1
//C����́w�z��/�|�C���^/�\���́x���g���đg�񂾃e���v���[�g�ł��B
// ���ɊȈՓI�ł���
// �E�V�[���J��(�O���[�o���ϐ���if���Ŏ���)
// �E�C���v�b�g�V�X�e��(�O���[�o���ϐ��̗��p�ɂ�����)
// �E�~�̓����蔻��(�x�N�g�����g�킸�Ɏ���)
// �Ȃǂ�����Ă��܂��B
// �쐬����Q�[���̉��n�Ƃ��Ďg�����́w�ǂ�ŗ����ł��邩�H�x�Ŋw�K�i�x���m�F���Ă��������B
// ���ȏ���Dxlib�̃��t�@�����X�����Ȃ���̗����ō\���܂���B
// ������Ȃ��w����C�̊w�K����蒼���Ă��������B

/*�\��*/
//�w�z��/�|�C���^/�\���́x���g�p���邱�ƂŁA
// �O��܂ŃO���[�o���ϐ��Ŗ���������Ă������Ƃ𑽏��X�}�[�g�ɂ��Ă��܂��B
// ���ɕ����̕Ԃ�l���~����������ʂŎg�p���Ă��܂��B
// �V�[���̐؂�ւ��͑O�񓯗l���s���\�b�h��؂�ւ��鎖�ŃV�[���Ǘ������Ă��܂��B
// �܂��A�V�[���Ǘ��ɂ͗񋓌^��p���Ă��܂��B

/*����*/
//fps�̍��ɂ�鋓���̈Ⴂ�͍l�����Ă��܂���B
//���ɂ��A�I�u�W�F�N�g�̑��x�Ȃǂ��ς���Ă��܂��܂��B


//Scene�Ǘ��p
enum SceneKind
{
	GAMEENED,
	TITLESCENE,
	GAMESCENE
};

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
	SceneKind nextScene;//Scene�Ǘ��p

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