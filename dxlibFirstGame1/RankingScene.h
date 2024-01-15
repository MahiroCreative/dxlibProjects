#pragma once
#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class RankingScene
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���X�V�p
	int _countFrame;//�^�C�}�p
public:
	/*�R���X�g���N�^*/
	RankingScene() :
		_nextScene(SceneKind::GAMESCENE),
		_countFrame(0)
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
		DrawString(600, 480, "RankingScene", GetColor(255, 255, 255));
	}

};