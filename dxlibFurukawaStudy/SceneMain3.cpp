#include <DxLib.h>
#include "SceneMain3.h"
// �w�b�_�[�ł̓N���X�̃v���g�^�C�v�錾�̂�
// �\�[�X�t�@�C�����ŃC���N���[�h���s��
#include "Player3.h"

SceneMain::SceneMain() :
	m_frameCount(0)
{
	// �����܂ł̓����o�[�̃������m�ۂ̓R���X�g���N�^��
	m_pPlayer = new Player;
}

SceneMain::~SceneMain()
{
	// �����܂ł̓����o�[�̉���̓f�X�g���N�^��
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneMain::Init()
{
	//for (int i = 0; i < kPlayerNum; i++)
	m_pPlayer->Init();
}

// ���t���[���̏���
void SceneMain::Update()
{
	m_frameCount++;

	m_pPlayer->Update();
}

// Update�ŏ����������ʂ𔽉f�������\����Draw�ōs��
void SceneMain::Draw() const
{
	// Color�Ɋւ���
	// ��2Byte����R,G,B�̒l���������Ă���Ǝv����
	DrawFormatString(8, 8, 0xffffff, "%d", m_frameCount);

	m_pPlayer->Draw();
}
