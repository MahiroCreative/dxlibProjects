#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
//#include "GameScene.h"

/*�V�[���Ǘ��p*/
/// <summary>
/// �V�[���Ǘ��p�̒萔�S
/// </summary>
namespace SceneKind
{
	enum SceneName
	{
		ENDGAME,
		TITLESCENE,
		GAMESCENE,
	};
}

/*�N���X��`*/
/// <summary>
/// �V�[���Ǘ�����}�l�[�W���[�N���X
/// </summary>
class SceneManager
{
private:
	/*�����o�ϐ�*/
	//�V�[�������p
	SceneBase* nowScene = nullptr;//���݂̃V�[��
	//�V�[���m�ۗp
	TitleScene* titleScene = nullptr;
	//GameScene* gameScene = nullptr;
public:
	/*static�����o�ϐ�*/
	//�V�[���X�V�p
	static SceneKind::SceneName s_nextScene;

	/*�R���X�g���N�^*/
	SceneManager()
	{
		//�V�[���̍쐬
		titleScene = new TitleScene();
		//gameScene = new GameScene();
		//Input first.
		nowScene = titleScene;
		//nextScene.
		s_nextScene = SceneKind::TITLESCENE;
	}

	/*�����o�֐�*/
	//�����̍X�V
	bool Update()
	{
		/*�V�[���v�Z����*/
		s_nextScene = nowScene->Update();

		/*�V�[���`�揈��*/
		nowScene->Draw();

		/*�V�[���ύX�E�I������*/
		switch (s_nextScene)
		{
		case SceneKind::TITLESCENE://titleScene.
			nowScene = titleScene;
			break;
		case SceneKind::GAMESCENE://gameScene.
			//nowScene = gameScene;
			break;
		case SceneKind::ENDGAME://�Q�[���I��
			//���������
			delete titleScene;
			//delete gameScene;
			//return.
			return false;
		}

		/*����I��*/
		return true;
	}
};

