#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	/*�����o�ϐ�*/
	//�V�[�������p
	SceneBase* nowScene = nullptr;//���݂̃V�[��
	//�V�[���m�ۗp
	TitleScene* titleScene = nullptr;
	GameScene* gameScene = nullptr;
	//�V�[���X�V�p
	SceneBase::SceneKind  _nextScene;
public:
	/*�R���X�g���N�^*/
	SceneManager()
	{
		//�V�[���̍쐬
		titleScene = new TitleScene();
		gameScene = new GameScene();
		//Input first.
		nowScene = titleScene;
		//nextScene.
		_nextScene = SceneBase::SceneKind::titleScene;
	}

	/*�����o�֐�*/
	//�����̍X�V
	bool Update()
	{
		/*�V�[���v�Z����*/
		_nextScene = nowScene->Update();

		/*�V�[���`�揈��*/
		nowScene->Draw();

		/*�V�[���ύX�E�I������*/
		switch (_nextScene)
		{
		case SceneBase::SceneKind::titleScene://titleScene.
			nowScene = titleScene;
			break;
		case SceneBase::SceneKind::gameScene://gameScene.
			nowScene = gameScene;
			break;
		case SceneBase::SceneKind::gameEnd://�Q�[���I��
			//���������
			delete titleScene;
			delete gameScene;
			//return.
			return false;
		}

		/*����I��*/
		return true;
	}
};

