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
// �O��܂Ŗ������O���[�o���ϐ��Ȃǂł���Ă������Ƃ𑽏����������Ă��܂��B
// �y��F�z
// �E�V�[���Ǘ����|�C���^�ł�����Ƃ����X�}�[�g��
// �E�e�ۂȂǕ������݂���f�[�^��z��ňꊇ�Ǘ�
// �E�G�l�~�[/�v���C���[/�e�ۂ̃p�����[�^�f�[�^���\���̂łP�ɓZ�߂�
// �E�|���^�̓V�[���Ǘ��ɗ��p(�Ԃ�l�ł̂����ƌ����͕ς��Ȃ�)
// �EInput�n�̓|�C���^�ƍ\���̂��g�p���Ă���B
// �E�|�C���^�̎g�p�ő��d���[�v�\���̉���
// �V�[���̐؂�ւ��͑O�񓯗l���s���\�b�h��؂�ւ��鎖�ŃV�[���Ǘ������Ă��܂��B
// �܂��A�V�[���Ǘ��ɂ͗񋓌^��p���Ă��܂��B
//�y���[�v�\�����P�F�z
//�@�O��܂ł̍\�����ƃV�[�����ɃQ�[�����[�v�����݂��AMain���[�v���ɃV�[�����[�v�����葽�d���[�v���������Ă���B
//�@���d���[�v�\���͂Ȃ�ׂ����P���ׂ��ł����ɁA���[�v�̒��Ƀ��[�v������ɂ����fps�����肵�Ȃ��B
//�@���̂��߃��[�v�\���̉������s�����߂ɃI�u�W�F�N�g���W�n�̃|�C���^�̗��p���������Ă���B

/*�Q�[���̎d�l*/
//�E�^�C�g�����
//	-START : �Q�[���V�[���Ɉړ�
//  -RANK: �����L���O�V�[���Ɉړ�
//	-END : �Q�[���I��
//�E�Q�[���V�[��
// - Player :WASD�œ����B�}�E�X���N���b�N�Œe�𔭎˂���B�G�l�~�[�̒e��������ƃ^�C�g���ɖ߂�B�e�͘A�˂ł���B
// - Enemy:�㉺�ɓ����B���Ԋu�Œe�𔭎ˁB�����тɒe�̑��x�������Ȃ�B�v���C���[�̒e��������ƃX�R�A���㏸����B�e���������Ă�Ԃ͐F���ς��B�e�ۂ���x�ɕ����͂ȂĂ�B
// - Score:�E��ɕ\���B���݂̃X�R�A���\�������B
//�E�����L���O�V�[��
// - �Q�[�����N�����Ă���Ԃ�MAXSCORE���\�������B�Q�[�����I������ƒl��0�ɖ߂�B

/*����*/
//fps�̍��ɂ�鋓���̈Ⴂ�͍l�����Ă��܂���B
//���ɂ��A�I�u�W�F�N�g�̑��x�Ȃǂ��ς���Ă��܂��܂��B

/*Scene��ފǗ��p*/
enum SceneKind
{
	GAMEENED,
	TITLESCENE,
	GAMESCENE,
	RANKINGSCENE
};

/*�O���[�o���萔*/
constexpr int MAXPLAYERBULLET = 3;
constexpr int MAXENEMYBULLET = 8;

/*�O���[�o���ϐ�*/
int MaxScore = 0;

/*�v���g�^�C�v�錾*/
void TitleScene(SceneKind* _nextScene);
void GameScene(SceneKind* _nextScene);
void RankingScene(SceneKind* _nextScene);


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

	/*�V�[���Ǘ��p*/
	SceneKind nextScene;
	//������
	nextScene = SceneKind::TITLESCENE;

	/*�V�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�V�[���J�ڏ���*/
		if (nextScene == SceneKind::TITLESCENE)
		{
			TitleScene(&nextScene);
		}
		else if (nextScene == SceneKind::GAMESCENE)
		{
			GameScene(&nextScene);
		}
		else if (nextScene == SceneKind::RANKINGSCENE)
		{
			RankingScene(&nextScene);
		}
		else if (nextScene == SceneKind::GAMEENED)
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

/*�V�[���֐�*/
void TitleScene(SceneKind* _nextScene)
{
	//Player
	struct Player
	{
		int X;
		int Y;
		int R;
	};
	//Enemy
	struct Enemy
	{
		int X;
		int Y;
		int R;
	};
	//EnemyBullet
	struct PlayerBullet
	{
		int X;
		int Y;
		int R;
	};
	//PlayerBullet
	struct EnemyBullet
	{
		int X;
		int Y;
		int R;
	};

}
void GameScene(SceneKind* _nextScene)
{

}
void RankingScene(SceneKind* _nextScene)
{

}

/*Input�֐�*/
//Key�t���O�Ǘ�
struct IsKeyInput
{
	bool isInputEnterHold = false;//Enter�p�̕ϐ�
	bool isInputUpHold = false;//Up�p�̕ϐ�
	bool isInputDownHold = false;//Down�p�̕ϐ�
};
//Enter�������ꂽ���ǂ����𔻒肷��֐�
bool InputEnter(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && !_isKey->isInputEnterHold)
	{
		_isKey->isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		_isKey->isInputEnterHold = false;
	}

	return false;
}
//Up�������ꂽ���ǂ����𔻒肷��֐�
bool InputUp(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_UP) && !_isKey->isInputDownHold)
	{
		_isKey->isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		_isKey->isInputDownHold = false;
	}

	return false;
}
//Down�������ꂽ���ǂ����𔻒肷��֐�
bool InputDown(IsKeyInput* _isKey)
{
	if (CheckHitKey(KEY_INPUT_DOWN) && !_isKey->isInputUpHold)
	{
		_isKey->isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		_isKey->isInputUpHold = false;
	}

	return false;
}