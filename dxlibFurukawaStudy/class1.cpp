#include "DxLib.h"

// �萔
namespace
{
	// �����z�u
	constexpr int kStartPosX = 320;
	constexpr int kStartPosY = 240;

	// �ړ����x
	constexpr int kSpeed = 4;
}

class Player
{
public:
	// �����o�ϐ��ł��邱�Ƃ��킩��悤��m_(���[���ɏ]���΂Ȃ�ł��悢��)��擪�ɂ���
	int m_handle;		// �O���t�B�b�N�n���h��
	int m_posX;		// �\�����WX
	int m_posY;		// �\�����WY
	bool m_isTurn;	// ���E���]�t���O

	// �R���X�g���N�^	���������m�ۂ������_�ŏ���ɌĂ΂��֐�
	Player();				// ���������R���X�g���N�^
	Player(int x, int y);	// �����ŏ����ʒu��ݒ�ł���R���X�g���N�^

	// �f�X�g���N�^		������������������_�ŏ���ɌĂ΂��֐�
	~Player();

	// �����o�֐�
	void Init();	// ������
	void Update();	// ���t���[���̍X�V
	void Draw();	// �`��
};

// Player�N���X�̃R���X�g���N�g
// ��������
Player::Player()
{
	// �O���t�B�b�N�̃��[�h
	m_handle = LoadGraph("data/player.png");

	m_posX = kStartPosX;
	m_posY = kStartPosY;

	// �O���t�B�b�N���]�t���O
	m_isTurn = false;
}
// ��������
Player::Player(int x, int y)
{
	// �O���t�B�b�N�̃��[�h
	m_handle = LoadGraph("data/player.png");

	m_posX = x;
	m_posY = y;

	// �O���t�B�b�N���]�t���O
	m_isTurn = false;
}

// Player�N���X�̃f�X�g���N�^
Player::~Player()
{
	// ����������������Ƃ��ɕK���Ă�łق�������������
	DeleteGraph(m_handle);
}

// �����o�֐��̎���
// �֐����̑O�ɃN���X��::�@�������Ă���Ă��̃N���X��Init�֐��ł��A�Ɛ錾����
void Player::Init()
{
	//����������
}

void Player::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_UP)
	{
		m_posY -= kSpeed;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		m_posY += kSpeed;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		m_posX -= kSpeed;
		m_isTurn = false;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_posX += kSpeed;
		m_isTurn = true;
	}
}

void Player::Draw()
{
	if (m_isTurn)
	{
		DrawTurnGraph(m_posX, m_posY, m_handle, false);
	}
	else
	{
		DrawGraph(m_posX, m_posY, m_handle, false);
	}
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	// �v���C���[
	Player player;				// ���������Ő錾
	//	Player player2(500, 20);	// ��������Ő錾	������ƌÂ�
	Player player2{ 500, 20 };	// ��������Ő錾	�ŐV�͔g������

	// �v���C���[�̏�����
	player.Init();
	player2.Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		player.Update();
		player2.Update();

		// �`��
		player.Draw();
		player2.Draw();

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