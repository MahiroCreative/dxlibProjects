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
	IntVector _charaColPos;//�L�����N�^�̃R���W�����̈ʒu
	IntVector _bulletPos;//�e�ۂ̈ʒu
	IntVector _bulletColPos;//�e�ۂ̃R���W�����̈ʒu
	int _charaHandle;//�L�����̉摜�n���h��
	int _charaSpeed;//�L�����̈ړ����x
	int _charaColR;//�L�����R���W�����̔��a
	int _bulletColR;//�e�ۃR���W�����̔��a
	int _debugInt;//Debug�p
	int _time;
	bool _isHitFlag;//�����蔻��t���O
public:
	/*�R���X�g���N�^*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_charaPos(240, 240),
		_charaColPos(_charaPos.X + 23, _charaPos.Y + 20),
		_charaColR(16),
		_charaHandle(-1),
		_charaSpeed(4),
		_bulletPos(800,320),
		_bulletColPos(800, 320),
		_bulletColR(8),
		_isHitFlag(false)
	{
		_charaHandle = LoadGraph("Chara.png");
	};
	/*�����o�֐�*/
	//�����̍X�V
	SceneKind Update()
	{

		/*�L�����X�V*/
		//�ړ�����
		//up.
		if (MyKeyInput::isHoldKey(KEY_INPUT_UP) && _charaPos.Y > 0)
		{
			_charaPos.Y -= _charaSpeed;
		}
		//down.
		if (MyKeyInput::isHoldKey(KEY_INPUT_DOWN) && _charaPos.Y < 680)
		{
			_charaPos.Y += _charaSpeed;
		}
		//left.
		if (MyKeyInput::isHoldKey(KEY_INPUT_LEFT))
		{
			_charaPos.X -= _charaSpeed;
		}
		//right.
		if (MyKeyInput::isHoldKey(KEY_INPUT_RIGHT))
		{
			_charaPos.X += _charaSpeed;
		}
		//�R���W�����ʒu�̍X�V
		_charaColPos.X = _charaPos.X + 23;
		_charaColPos.Y = _charaPos.Y + 20;

		/*�e�ۍX�V*/
		//�e��1:�ړ�
		_bulletPos.X -= 8;
		_bulletColPos.X -= 8;
		//�e��2:�ړ�
		//�e��3:�ړ�

		/*�L���������蔻��*/
		int HitLength = _charaColR + _bulletColR;
		IntVector delVec = _charaColPos - _bulletColPos;
		int delLength = delVec.Length();
		//hitCount = delLength;
		
		if (HitLength > delLength)
		{
			_isHitFlag = true;
		}
		else
		{
			_isHitFlag = false;
		}

		_time = MyKeyInput::HoldKeyTime(KEY_INPUT_Z);

		/*�V�[���J�ڏ���*/
		//Enter�L�[����������Title�V�[���ɑJ��
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}

		return _nextScene;
	}
	//�`��X�V
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));

		//�L�����N�^�[�̕`��
		DrawGraph(_charaPos.X, _charaPos.Y, _charaHandle, TRUE);

		//�L�����N�^�[�̃R���W�����̕`��
		DrawCircle(_charaColPos.X, _charaColPos.Y, _charaColR, GetColor(0,255,0), 0);

		//�e�ۂ̕`��
		DrawCircle(_bulletPos.X,_bulletPos.Y,8, GetColor(255, 0, 0),1);

		//�e�ۂ̃R���W�����̕`��
		DrawCircle(_bulletColPos.X, _bulletColPos.Y, _bulletColR, GetColor(0, 0, 255), 0);
	}
	//�f�o�b�O�p�̕`��X�V
	void DebugDraw()
	{
		DrawFormatString(10,700,GetColor(0,0,255), "%d", _isHitFlag);
		DrawFormatString(30, 700, GetColor(0, 0, 255), "%d", _time);
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