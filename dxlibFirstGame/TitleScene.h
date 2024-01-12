#pragma once
#include "SceneBase.h"
#include "SceneManager.h"

class TitleScene :
	public SceneBase
{
private:
	IntVector _arrowPos;
	IntVector _movePos;
	IntVector _tempPos;
	int _inputTime;
	int _bgmHandle;
	int _nextScene;
public:
	/*�R���X�g���N�^*/
	TitleScene()
	{
		/*�ϐ�������*/
		_arrowPos = IntVector(560,480);
		_movePos = IntVector(560,520);
		_tempPos = IntVector();
		_inputTime = -1;
		_nextScene = SceneKind::TITLESCENE;
		_bgmHandle = LoadSoundMem("Resources/bgm_title.mp3");
		/*�������s*/
		//BGM�Đ�
		PlaySoundMem(_bgmHandle, DX_PLAYTYPE_BACK);
	}
	/*�����o�֐�*/
	//frame���̌v�Z����
	int Update() override
	{
		/*Key���͂̊m�F*/
		MyKeyInput::Update();

		/*���͑���*/
		//�㉺�L�[
		if (MyKeyInput::isDownKey(KEY_INPUT_UP) || MyKeyInput::isDownKey(KEY_INPUT_DOWN))
		{
			//����ւ�
			_tempPos = _arrowPos;
			_arrowPos = _movePos;
			_movePos = _tempPos;
		}
		//�G���^�[�L�[
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			//���̈ʒu�ŃV�[���J�ڐ��ύX
			if (_arrowPos.Y == 520)
			{
				_nextScene = SceneKind::GAMESCENE;
			}
			else
			{
				_nextScene = SceneKind::ENDGAME;
			}
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