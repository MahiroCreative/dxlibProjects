#pragma once
#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene2
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
public:
	/*�R���X�g���N�^*/
	GameScene2() :
		_nextScene(SceneKind::GAMESCENE2)
	{
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{
		//Enter�L�[����������w��V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMEEND;
		}

		return _nextScene;
	}
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(600, 480, "gameScene2", GetColor(255, 255, 255));
	}

};