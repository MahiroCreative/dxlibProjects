#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
public:
	/*�R���X�g���N�^*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE)
	{
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{
		//Enter�L�[����������w��V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}
		return _nextScene;
	}
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(600, 480, "gameScene", GetColor(255, 255, 255));
	}
	/// <summary>
	/// �C���X�^���X�̏�����
	/// </summary>
	void Init()
	{
		//�����o�ϐ��̏�����
		_nextScene = SceneKind::GAMESCENE;
	}
};