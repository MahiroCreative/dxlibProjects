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

/*Scene�Ǘ�*/
struct SceneManager
{
	SceneKind _backScene = SceneKind::TITLESCENE;
	SceneKind _nextScene = SceneKind::TITLESCENE;
};

/*Input�Ǘ�*/
struct KeyInput
{
	bool isInputEnterHold = false;//Enter�p�̕ϐ�
	bool isInputUpHold = false;//Up�p�̕ϐ�
	bool isInputDownHold = false;//Down�p�̕ϐ�
};

/*�e�V�[���p�̕ϐ��쐬*/
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
//Score
struct Score
{
	int NowScore;
	int MaxScore;
};
//Timer
struct FrameCount
{
	int count;
};
//�O���[�o���ϐ�
constexpr int MAXPLAYERBULLET = 3;
constexpr int MAXENEMYBULLET = 8;

/*�v���g�^�C�v�錾*/
void AllSceneInit(Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score);
void TitleScene(SceneManager* _sceneManager);
void GameScene(SceneManager* _sceneManager, Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score);
void RankingScene(SceneManager* _sceneManager, Score* _score);


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

	/*�Q�[���p�ϐ��̍쐬*/
	SceneManager sceneManager;
	Player player;
	Enemy enemy;
	PlayerBullet playerBullet[MAXPLAYERBULLET];
	EnemyBullet enemyBullet[MAXENEMYBULLET];
	Score score;

	/*�Q�[�����[�v��*/
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�V�[��������*/
		//�V�[���ύX���ɏ�����
		if (sceneManager._backScene != sceneManager._nextScene)
		{
			AllSceneInit(&player, &enemy, playerBullet, enemyBullet, &score);
		}

		/*�V�[���J�ڏ���*/
		if (sceneManager._nextScene == SceneKind::TITLESCENE)
		{
			TitleScene(&sceneManager);
		}
		else if (sceneManager._nextScene == SceneKind::GAMESCENE)
		{
			GameScene(&sceneManager, &player, &enemy, playerBullet, enemyBullet, &score);
		}
		else if (sceneManager._nextScene == SceneKind::RANKINGSCENE)
		{
			RankingScene(&sceneManager, &score);
		}
		else if (sceneManager._nextScene == SceneKind::GAMEENED)
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

/*�e�V�[��*/
void AllSceneInit(Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet,Score* _score)
{

}
void TitleScene(SceneManager* _sceneManager)
{
	/*���[�J���ϐ�*/

	//�^�C�g�����S
	SetFontSize(80);//�t�H���g�T�C�Y�ύX
	DrawString(440, 240, "DxlibGame", GetColor(255, 255, 255));
	SetFontSize(40);//�t�H���g�T�C�Y��
	DrawString(460, 320, "-GameTemplate2-", GetColor(255, 255, 255));
	SetFontSize(20);//�t�H���g�T�C�Y������
	//�Q�[���V�[���e�L�X�g
	DrawString(600, 440, "START", GetColor(255, 255, 255));
	//�Q�[���G���h�e�L�X�g
	DrawString(600, 480, "END", GetColor(255, 255, 255));


	/*DebugDraw����*/
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��
}
void GameScene(SceneManager* _sceneManager, Player* _player, Enemy* _enemy, PlayerBullet* _playerBullet, EnemyBullet* _enemyBullet, Score* _score)
{

}
void RankingScene(SceneManager* _sceneManager, Score* _score)
{

}

/*Input�֐�*/
//Enter�������ꂽ���ǂ����𔻒肷��֐�
bool InputEnter(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && !_Key->isInputEnterHold)
	{
		_Key->isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		_Key->isInputEnterHold = false;
	}

	return false;
}
//Up�������ꂽ���ǂ����𔻒肷��֐�
bool InputUp(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_UP) && !_Key->isInputDownHold)
	{
		_Key->isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		_Key->isInputDownHold = false;
	}

	return false;
}
//Down�������ꂽ���ǂ����𔻒肷��֐�
bool InputDown(KeyInput* _Key)
{
	if (CheckHitKey(KEY_INPUT_DOWN) && !_Key->isInputUpHold)
	{
		_Key->isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		_Key->isInputUpHold = false;
	}

	return false;
}