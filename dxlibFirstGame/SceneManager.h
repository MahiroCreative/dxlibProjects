#pragma once
#include "SceneBase.h"
#include "TitleScene.h"

/*�O���[�o���ϐ�*/
enum SceneKind
{
	gameEnd,
	titleScene,
};

class SceneManager
{
private:
	/*�����o�ϐ�*/
	//�V�[�������p
	SceneBase* nowScene = nullptr;//���݂̃V�[��
	//�V�[���m�ۗp
	TitleScene* titleScene = nullptr;
	//�V�[���X�V�p
	SceneBase::SceneKind  _nextScene;
public:
	/*�R���X�g���N�^*/
	SceneManager()
	{
		//�V�[���̍쐬
		titleScene = new TitleScene();
		//Input first.
		nowScene = titleScene;
	}

	/*�����o�֐�*/
	//�����̍X�V
	bool Update()
	{
		/*�V�[���v�Z����*/
		_nextScene = nowScene->Update();

		/*�V�[���`�揈��*/
		nowScene->Draw();

		/*�V�[���ύX����*/

		/*�Q�[���I���m�F*/
		//�쐬��
		if (_nextScene == SceneKind::gameEnd){return false;}
		else{return true;}
	}
};

