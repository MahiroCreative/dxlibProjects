#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene1
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
public:
	/*�R���X�g���N�^*/
	GameScene1() :
		_nextScene(SceneKind::GAMESCENE1)
	{
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{
		//Enter�L�[����������w��V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMESCENE2;
		}
		return _nextScene;
	}
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(600, 480, "gameScene1", GetColor(255, 255, 255));
	}
};