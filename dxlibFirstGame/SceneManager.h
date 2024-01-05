#pragma once
#include "SceneBase.h"
#include "GameScene.h"
#include "TitleScene.h"

class SceneManager
{
private:
	/*�����o�ϐ�*/
	//�V�[���X�V�p
	SceneBase* backScene = nullptr;//���O�̃V�[��
	SceneBase* nowScene = nullptr;//���݂̃V�[��
	SceneBase* nextScene = nullptr;//���̃V�[��
	//�V�[���m�ۗp
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
public:
	/*�R���X�g���N�^*/
	SceneManager()
	{
		//�V�[���̍쐬
		//gameScene = new GameScene();
		titleScene = new TitleScene();
		//Input first.
		nowScene = titleScene;
	}

	/*�����o�֐�*/
	//�����̍X�V
	void Update()
	{
		nowScene->Update(nextScene);

		/*�V�[���ύX*/
		if (nextScene != nullptr)
		{
			nowScene = nextScene;
			nextScene = nullptr;
		}
	}
	//�`��̍X�V
	void Draw()
	{
		nowScene->Draw();
	}
	//���̍X�V
	void Soud()
	{
		nowScene->Sound();
	}
};

