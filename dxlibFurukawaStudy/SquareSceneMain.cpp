#include "SquareSceneMain.h"
#include <DxLib.h>
#include "SquareSceneMain.h"

namespace
{
	const unsigned int kWhiteColor = GetColor(255, 255, 255);
	const unsigned int kRedColor = GetColor(255, 0, 0);
}

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player.Init();
	m_player.SetFill(true);		// �v���C���[�̋�`�͓h��Ԃ�
	m_player.SetMouseTrase(true);	// �v���C���[�̋�`�̓}�E�X�ɒǏ]

	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Init();	// rect�̏�����

		m_rect[i].SetRandom();
	}
}

void SceneMain::Update()
{
	m_player.Update();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Update();	// rect�̖��t���[���̍X�V����
		// �ړ���̏������ē����蔻������
		if (m_player.IsCollision(m_rect[i]))
		{
			// �������Ă���ꍇ�̏���
			m_rect[i].SetColor(kRedColor);
		}
		else
		{
			// �������Ă��Ȃ��ꍇ�̏���
			m_rect[i].SetColor(kWhiteColor);
		}
	}
}

void SceneMain::Draw()
{
	m_player.Draw();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Draw();	// rect�̕`��
	}
}

void SceneMain::End()
{
}