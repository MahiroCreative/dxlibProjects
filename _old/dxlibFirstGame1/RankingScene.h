#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class RankingScene
{
private:
	/*�����o�ϐ�*/
	SceneKind _nextScene;//�V�[���J�ڗp
public:
	/*�����o�ϐ�*/
	static int _maxScore;
	/*�R���X�g���N�^*/
	RankingScene() :
		_nextScene(SceneKind::RANKING)
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
		//�X�R�A�̕\��
		SetFontSize(80);//�t�H���g�T�C�Y�㏸
		DrawFormatString(400, 240, GetColor(255, 255, 2555), "MaxScore:%d", _maxScore);
		SetFontSize(20);//�t�H���g�T�C�Y���f�t�H���g�ɖ߂�
		DrawFormatString(480, 500, GetColor(255, 255, 255), "-- Return with enter --");

	}
	void DebugDraw()
	{
		//���݂̃V�[������`��
		DrawString(8, 8, "SceneName:RankingScene", GetColor(0, 255, 255));
	}
	/// <summary>
	/// �C���X�^���X�̏�����
	/// </summary>
	void Init()
	{
		//�����o�ϐ��̏�����
		_nextScene = SceneKind::RANKING;
	}

};
int RankingScene::_maxScore = 0;