#include <cassert>
#include "SceneManager.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_title(),		// �N���X�̏���������()�̒��ɃR���X�g���N�^�̈���������
	m_main(),		// ����͂ǂ̃V�[�����R���X�g���N�^�͈�����v�����Ȃ��̂�
	m_result()		// m_title()�̂悤�ȏ�������OK
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// ����������
	// ���s�������V�[���̏��������s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Init();
		break;
	case kSceneKindMain:
		m_main.Init();
		break;
	case kSceneKindResult:
		m_result.Init();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::Update()
{
	// �O�̃t���[���̎��_�ŏ������I����Ă�����V�[���̐؂�ւ�
	// �V�[���̐؂�ւ����s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		if (m_title.IsSceneEnd())
		{
			m_title.End();		// ���s���Ă����V�[���̏I������

			// �Q�[���V�[���֑J��
			m_runScene = kSceneKindMain;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_main.Init();		// �ύX��̃V�[���̏�����
		}
		break;
	case kSceneKindMain:
		// �I�����Ă�����SceneResult�ɐ؂�ւ���
		if (m_main.IsSceneEnd())
		{
			// �V�[����؂�ւ���
			m_main.End();		// ���s���Ă����V�[���̏I������

			m_runScene = kSceneKindResult;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_result.Init();		// �ύX��̃V�[���̏�����
		}
		break;
	case kSceneKindResult:
		if (m_result.IsSceneEnd())
		{
			m_result.End();		// ���s���Ă����V�[���̏I������

			// �^�C�g���֑J��
			m_runScene = kSceneKindTitle;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_title.Init();		// �ύX��̃V�[���̏�����
		}
		break;
	default:
		assert(false);
		break;
	}

	// ���s���̃V�[���̍X�V���s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Update();
		break;
	case kSceneKindMain:
		m_main.Update();
		break;
	case kSceneKindResult:
		m_result.Update();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::Draw()
{
	// ���s���̃V�[���̕`����s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Draw();
		break;
	case kSceneKindMain:
		m_main.Draw();
		break;
	case kSceneKindResult:
		m_result.Draw();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.End();
		break;
	case kSceneKindMain:
		m_main.End();
		break;
	case kSceneKindResult:
		m_result.End();
		break;
	default:
		assert(false);
		break;
	}
}