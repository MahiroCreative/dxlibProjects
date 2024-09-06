#pragma once
#include "MyDxlibCommon.h"
#include "DxLib.h"

class Bullet
{
public:
	/*public�����o�ϐ�*/
	int X=NULL;//X���W
	int Y=NULL;//Y���W
	/*�R���X�g���N�^*/
	Bullet();
	/*Init*/
	void Init(int x,int y,int r,int speed,unsigned int color,bool visible);
	/*Getter*/
	bool getVisible();
	int getR();
	/*�����o�֐�*/
	void Update();
	void Draw();
	void DebugDraw();
private:
	/*private�����o�ϐ�*/
	int _r=NULL;
	int _speed=NULL;
	unsigned int _color=NULL;
	bool _isVisible = false;
};

/*�R���X�g���N�^*/
/// <summary>
/// Bullet�̃R���X�g���N�^
/// </summary>
Bullet::Bullet(){}

/*Init*/
/// <summary>
/// ����������
/// </summary>
/// <param name="x">X���W</param>
/// <param name="y">Y���W</param>
/// <param name="r">���a</param>
/// <param name="speed">���x</param>
/// <param name="color">�F</param>
/// <param name="visible">�\���t���O</param>
void Bullet::Init(int x, int y, int r, int speed, unsigned int color, bool visible)
{
	X = x;
	Y = y;
	_r = r;
	_speed = speed;
	_color = color;
	_isVisible = visible;
}

/*Getter*/
/// <summary>
/// �\���t���O�̎擾
/// </summary>
bool Bullet::getVisible()
{
	return _isVisible;
}
/// <summary>
/// ���a�̎擾
/// </summary>
/// <returns></returns>
int Bullet::getR()
{
	return _r;
}

/*�����o�֐�*/
/// <summary>
/// �v�Z�����̍X�V
/// </summary>
void Bullet::Update()
{
	//��ʓ��ł̂ݑO�i
	if (X > -80 && X < 1360)
	{
		X += _speed;
		//_isVisible = false;
	}
	else
	{
		_isVisible = false;
	}
}
/// <summary>
/// �\�������̍X�V
/// </summary>
void Bullet::Draw()
{
	if (_isVisible)
	{
		DrawCircle(X, Y, _r, _color, 1);
	}

}
/// <summary>
/// Debug�\���̍X�V
/// </summary>
void Bullet::DebugDraw()
{

}