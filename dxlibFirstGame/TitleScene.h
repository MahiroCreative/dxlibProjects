#pragma once
#include "SceneBase.h"

class TitleScene :
	public SceneBase
{
private:
	IntVector _arrowPos;
	IntVector _movePos;
	IntVector _tempPos;
	int _inputTime;
	int _bgmHandle;
	SceneBase::SceneKind _nextScene;
public:
	/*�R���X�g���N�^*/
	TitleScene()
	{
		/*�ϐ�������*/
		_arrowPos = IntVector(560,480);
		_movePos = IntVector(560,520);
		_tempPos = IntVector();
		_inputTime = -1;
		_nextScene = SceneKind::titleScene;
		_bgmHandle = LoadSoundMem("Resources/bgm_title.mp3");
		/*�������s*/
		//BGM�Đ�
		PlaySoundMem(_bgmHandle, DX_PLAYTYPE_BACK);
	}
	/*�����o�֐�*/
	//frame���̌v�Z����
	SceneBase::SceneKind Update() override
	{
		/*Key���͑���(���G��蒼��)*/
		if (_inputTime == -1)
		{
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
			{
				//����ւ�
				_tempPos = _arrowPos;
				_arrowPos = _movePos;
				_movePos = _tempPos;
				//�^�C�}�X�V
				_inputTime = 0;
			}
			else if (CheckHitKey(KEY_INPUT_RETURN))
			{
				if (_arrowPos.Y == 520)
				{
					_nextScene = SceneKind::gameEnd;
				}
				else
				{
					_nextScene = SceneKind::gameScene;
				}

			}

		}
		else if (_inputTime < 8 && _inputTime != -1)
		{
			_inputTime += 1;
		}
		else
		{
			_inputTime = -1;
		}

		/*�Ԃ�l*/
		return _nextScene;
	}
	//frame���̕`�揈��
	void Draw() const override
	{
		/*�����̕`��*/
		//Start.
		DrawString(600, 480, "START", GetColor(255, 255, 255));
		//End.
		DrawString(600, 520, "END", GetColor(255, 255, 255));
		//Arrow.
		DrawString(_arrowPos.X, _arrowPos.Y, "��", GetColor(255, 255, 255));
	}
};