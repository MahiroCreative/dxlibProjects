#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
	IntVector _charaPos;//�L�����N�^�̈ʒu
	int _charaHandle;
public:
	/*�R���X�g���N�^*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_charaPos(240,240),
		_charaHandle(-1)
	{
		_charaHandle = LoadGraph("Chara.png");
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{

		/*�L��������*/
		//up.
		if (MyKeyInput::isHoldKey(KEY_INPUT_UP))
		{
			_charaPos.Y -= 3;
		}
		//down.
		if (MyKeyInput::isHoldKey(KEY_INPUT_DOWN))
		{
			_charaPos.Y += 3;
		}
		//left.
		if (MyKeyInput::isHoldKey(KEY_INPUT_LEFT))
		{
			_charaPos.X -= 3;
		}
		//right.
		if (MyKeyInput::isHoldKey(KEY_INPUT_RIGHT))
		{
			_charaPos.X += 3;
		}


		/*�V�[���J�ڏ���*/
		//Enter�L�[����������Title�V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}

		return _nextScene;
	}
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));

		//�L�����N�^�[�̕`��
		DrawGraph(_charaPos.X,_charaPos.Y,_charaHandle,TRUE);
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