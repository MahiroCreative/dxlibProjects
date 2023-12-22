#pragma once
#include "SceneBase.h"
#include "GameScene.h"
#include "TitleScene.h"

class SceneManager
{
public:
	/*�����o�ϐ�*/
	//�V�[���X�V�p
	SceneBase* backScene = nullptr;//���O�̃V�[��
	SceneBase* nowScene = nullptr;//���݂̃V�[��
	SceneBase* nextScene = nullptr;//���̃V�[��
	//�V�[���m�ۗp
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;

	/*�R���X�g���N�^*/
	SceneManager()
	{
		//�V�[���̍쐬
		gameScene = new GameScene();
		titleScene = new TitleScene();
		//Input first.
		nowScene = gameScene;
	}

	/*�����o�֐�*/
	//�����̍X�V
	void Update()
	{
		nowScene->Update();
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

