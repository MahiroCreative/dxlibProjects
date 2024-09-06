#pragma once
#include "Enemy.h"
#include "MyDxlibCommon.h"
#include "DxLib.h"

class Player
{
public:
	/*public�����o�ϐ�*/
	int X = NULL;//x���W
	int Y = NULL;//y���W
	/*�R���X�g���N�^*/
	Player();
	/*Init*/
	void Init(int drawHandle, int x, int y, int r, int speed, bool visible, bool colVisible);
	/*Getter*/
	bool getShotFlag();
	int getR();
	/*�����o�֐�*/
	void Update();//�����̍X�V
	void Draw();//�\���̍X�V
	void DebugDraw();//Debug�\���̍X�V
private:
	/*private�����o�ϐ�*/
	int _drawHandle = -1;//�摜�n���h��
	int _r = NULL;//���a
	int _speed = NULL;//�X�s�[�h
	//�ύX�����\���̖������̂͂����ŏ�����
	unsigned int _colColer = ColorCode::LIME;//�R���W�����F
	int _scale = 1;//�X�P�[��
	int _rotate = 0;//��]�x
	bool _isShotFlag = false;//�V���b�g�t���O
	bool _isHit = false;//�����蔻��
	bool _isVisible = false;//�\������
	bool _isColVisible = false;//�R���W�����̕\������
	//Input�p�̕ϐ�
	IsKeyInput _isEnterInput{ false,false,KEY_INPUT_RETURN };//Enter.
	IsKeyInput _isUpInput{ false,false,KEY_INPUT_W };//Up.
	IsKeyInput _isDownInput{ false,false,KEY_INPUT_S };//Down.
	IsKeyInput _isLeftInput{ false,false,KEY_INPUT_A };//Left.
	IsKeyInput _isRightInput{ false,false,KEY_INPUT_D };//Right.
};

/*�R���X�g���N�^*/
/// <summary>
/// Player�̃R���X�g���N�^(�C���X�^���X�쐬�̂�)
/// </summary>
Player::Player(){}

/*Init*/
/// <summary>
/// �����o�ϐ��̏�����
/// </summary>
/// <param name="drawHandle">draw�n���h��</param>
/// <param name="x">X���W</param>
/// <param name="y">Y���W</param>
/// <param name="r">���a</param>
/// <param name="speed">�X�s�[�h</param>
/// <param name="visible">�\���t���O</param>
/// /// <param name="colVisible">�\���t���O</param>
void Player::Init(int drawHandle, int x, int y, int r, int speed, bool visible, bool colVisible)
{
	_drawHandle = drawHandle;
	X = x;
	Y = y;
	_r = r;
	_speed = speed;
	_isVisible = visible;
	_isColVisible = colVisible;
}

/*Getter*/
/// <summary>
/// �e�ۂ𔭎˂����ۂ�True�A����ȊO��False
/// </summary>
/// <returns>bool</returns>
bool Player::getShotFlag()
{
	return _isShotFlag;
}
/// <summary>
/// ���a�̎擾
/// </summary>
/// <returns></returns>
int Player::getR()
{
	return _r;
}

/*�����o�֐�*/
/// <summary>
/// �v�Z�̍X�V
/// </summary>
void Player::Update()
{
	/*KeyUpdate*/
	_isEnterInput = InputKeyUpdate(_isEnterInput);//Enter.
	_isUpInput = InputKeyUpdate(_isUpInput);//Up.
	_isDownInput = InputKeyUpdate(_isDownInput);//Donw.
	_isLeftInput = InputKeyUpdate(_isLeftInput);//Left.
	_isRightInput = InputKeyUpdate(_isRightInput);//Right.

	/*�ړ�����*/
	//Up.
	if (_isUpInput.IsHold == true)
	{
		Y -= _speed;
	}
	//Down.
	if (_isDownInput.IsHold == true)
	{
		Y += _speed;
	}
	//Left.
	if (_isLeftInput.IsHold == true)
	{
		X -= _speed;
	}
	//Right.
	if (_isRightInput.IsHold == true)
	{
		X += _speed;
	}

	/*PlayerBullet�̔���*/
	if (_isEnterInput.IsNow)//���ˎ�
	{
		_isShotFlag = true;
	}
	else//�񔭎ˎ�
	{
		_isShotFlag = false;
	}

}
/// <summary>
/// �\�������̍X�V
/// </summary>
void Player::Draw()
{
	//Player�̕`��
	if (_isVisible)
	{
		DrawRotaGraph(X, Y, 1, 0, _drawHandle, 1);
	}
}
/// <summary>
/// Debug�\���̍X�V
/// </summary>
void Player::DebugDraw()
{
	//�R���W�����̕`��
	if (_isColVisible)
	{
		DrawCircle(X, Y, _r, ColorCode::LIME, 0);
	}
}
