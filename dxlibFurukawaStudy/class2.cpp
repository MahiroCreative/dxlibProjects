#include "DxLib.h"
#include <cassert>

// �N���X
class Enemy
{
	// �����o�ϐ��A�����o�֐��ɂ�private,public�Ƃ�������������
	// �����o�ϐ��͑S��private:�ɂ��܂��傤

#if true
// public:��private:�����Ă��Ȃ��ꏊ�ɏ����������o��private�����o
	int m_pri000;	// private�����o

	// private:������ɏ����������o(�ϐ��A�֐�)��private�����o
private:
	int m_pri001;	// private�����o

	// public:������ɏ����������o(�ϐ��A�֐�)��public�����o
public:
	int m_pub000;	// public�����o

	void pubFunc();	// public�����o�̊֐�
	// private:,public: ���x�����Ă��悢
private:
	int m_pri002;	// private�����o
	void priFunc();	// private�����o�̊֐�
#endif

public:		// �O������̃A�N�Z�X�\�ɂ���

	// �����o�ϐ����͂��̃v���O�����������l�����������ł���̓����o�ϐ��A
	// �ƕ�����悤�ɖ��O��t���邱�Ƃ�����
	// �ϐ����̑O�� m_ ��������A		handle -> m_handle
	// �ϐ����̑O�� _ ��������A		handle -> _handle
	// �ϐ����̍Ō�� _ �������肷��	handle -> handle_
	// ���[���͂ǂ�ł��\��Ȃ����A�K�����ꂵ�ď���
	// �`�[������̏ꍇ�̓`�[���łǂ̂悤�ȃ��[���ɂ��邩���߂�
	int m_handle;	// �O���t�B�b�N�n���h��
	int m_posX;		// X���W
	int m_posY;		// Y���W
	int m_moveX;	// X�����̈ړ����W
	int m_moveY;	// Y�����̈ړ����W

	// �R���X�g���N�^
	// ���̂��쐬���ꂽ�Ƃ�(���������m�ۂ��ꂽ�Ƃ�)�����I�ɌĂяo�����֐�
	// �߂�l�����A�N���X���Ɠ����֐���
	Enemy();
	// �f�X�g���N�^
	// ��������������ꂽ�Ƃ������I�ɌĂ΂��֐�
	// �߂�l�����A�������ݒ�ł��Ȃ��@�֐����̓N���X���̑O��~(�`���_)������
	~Enemy();

	// �N���X�͍\���̂ɉ����ăN���X���Ŋ֐����쐬���邱�Ƃ��ł���
	// �N���X���̊֐��������o�֐��Ƃ���
	void Init();
	void Update();
	void Draw();
};

#if true
void Enemy::pubFunc()
{

}

void Enemy::priFunc()
{

}
#endif

// Enemy�N���X�̃R���X�g���N�g
// �R���X�g���N�^�Œl���������������ꍇ�͓��ʂȏ�����������
// �R���X�g���N�^�������q�Ƃ���

// �R���X�g���N�^�������q�Ɋւ���
// �R���X�g���N�^�������q���g���Ă��g��Ȃ��Ă����ʂ͓���
// �����R���X�g���N�^�������q���g��
// �E�������x�I�ɗL��
// �E�R���X�g���N�^�������q�������Ă܂��A�s�[��
Enemy::Enemy() :
	m_handle(-1),
	m_posX(320),
	m_posY(240),
	m_moveX(0),
	m_moveY(0)
{
	// �l��������������A0�N���A�����肷��

	// �����o�֐����瓯���N���X���̃����o�ϐ��ɃA�N�Z�X�ł���
	// �A�N�Z�X����ۂ�enemy.handle �̂悤�ȏ����������Ȃ��Ă� handle �݂̂ŃA�N�Z�X�ł���

	// �����o�ϐ��̓R���X�g���N�^�������q�ŏ���������悤�ɂ���
	m_handle = LoadGraph("data/obj.png");
	assert(m_handle != -1);
}

// Enemy�N���X�̃f�X�g���N�^
Enemy::~Enemy()
{
	// �I�����ɖY�ꂸ�ɂ���Ă����Ȃ��Ƃ����Ȃ�����������
	DeleteGraph(m_handle);
}

// �����o�֐��������������Ƃ��͊֐����̑O�� �N���X��:: �Ə���
void Enemy::Init()
{

}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	// �N���X������Ȃ�private�����o�Apublic�����o���ɃA�N�Z�X�\
	m_pub000 = 10;
	pubFunc();

	m_pri000 = 10;
	priFunc();

	DrawGraph(m_posX, m_posY, m_handle, false);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	Enemy enemy;

	// �����o�֐��̌Ăяo��
	// �����o�ϐ��Ɠ����� . (�h�b�g)�łȂ��Ń����o�֐����Ăяo��
	enemy.Init();

	// public�����o�ɂ̓N���X�O����A�N�Z�X�ł���
	// private�����o�ɂ̓N���X�O����A�N�Z�X�ł��Ȃ�
	// �N���X�O�H�@���̃N���X�̃����o�֐����̓N���X���B����ȊO�̓N���X�O
	// ������Enemy�N���X�̊O

	// public �����o�ɂ̓A�N�Z�X�\�A�g�p�\
	enemy.m_pub000 = 10;
	enemy.pubFunc();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���

		enemy.Draw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		// 16.66ms(16667�}�C�N���b)�o�߂���܂ő҂�
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}