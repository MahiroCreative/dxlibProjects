#pragma once
#include "Bullet.h"
#include "MyDxlibCommon.h"
#include "DxLib.h"

class Enemy
{
public:
	/*public�����o�ϐ�*/
	int X=NULL;//x���W
	int Y=NULL;//y���W
	/*�R���X�g���N�^*/
	Enemy();
	/*Init*/
	void Init(int x, int y, int r, int speed,int visible);
	/*Getter*/
	int getR();
	/*Setter*/
	void setColor(unsigned int color);
	/*�����o�֐�*/
	void Update();//�����̍X�V
	void Draw();//�\���̍X�V
	void DebugDraw();//Debug�\���̍X�V
private:
	/*private�����o�ϐ�*/
	int _r=NULL;//���a
	int _speed=NULL;//�X�s�[�h
	int _bulletSpeed=NULL;//�e�ۂ̑��x
	//�ύX�����\���̖������̂͂����ŏ�����
	unsigned int _color = ColorCode::AQUA;//�F
	unsigned int _hitColor = ColorCode::RED;//Hit�F
	bool _isHit = false;//�����蔻��
	bool _isVisible = false;//�\������
};

/*�R���X�g���N�^*/
/// <summary>
/// Enemy�̃R���X�g���N�^(�C���X�^���X�쐬�̂�)
/// </summary>
Enemy::Enemy(){}

/*Setter*/
/// <summary>
/// �F�̕ύX
/// </summary>
/// <param name="color">�J���[�R�[�h</param>
void Enemy::setColor(unsigned int color)
{
	_color = color;
}

/*Getter*/
/// <summary>
/// ���a�̎擾
/// </summary>
/// <returns>int</returns>
int Enemy::getR()
{
	return _r;
}

/*Init*/
void Enemy::Init(int x, int y, int r, int speed,int visible)
{
	X = x;
	Y = y;
	_r = r;
	_speed = speed;
	_isVisible = visible;
}

/// <summary>
/// �v�Z�����̍X�V
/// </summary>
void Enemy::Update()
{
	//�ړ�
	Y += _speed;
	//���]
	if (Y > 640 || Y < 80)
	{
		_speed = -_speed;
	}
}

/// <summary>
/// �\�������̍X�V
/// </summary>
void Enemy::Draw()
{
	if (_isVisible)
	{
		DrawCircle(X, Y, _r, _color, 1);
	}
	
}

void Enemy::DebugDraw()
{

}