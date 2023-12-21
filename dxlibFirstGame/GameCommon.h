#pragma once
#include "DxLib.h"

/// <summary>
/// ��ʃT�C�Y�Ȃǂ̋��ʒ萔
/// </summary>
namespace GameConst
{
	/*��ʃT�C�Y*/
	constexpr int ScreenSizeX = 1280;//��
	constexpr int ScreenSizeY = 720;//����
	/*���\�[�X�n���h��*/
	const int playerDrawHandle = LoadGraph("Resources\player.png");
}

struct Vector
{
public:
	/*�����o�ϐ�*/
	int _x,_y,_z;

	/*�R���X�g���N�^*/
	Vector():_x(0),_y(0),_z(0){}//0�x�N�g��
	Vector(int x, int y) :_x(x), _y(y), _z(0) {}//2�����x�N�g��
	Vector(int x, int y, int z) : _x(x), _y(y), _z(z) {}//3�����x�N�g��

	/*���Z�q�I�[�o�[���[�h*/
	//Add.
	Vector& operator+=(const Vector& right)
	{
		_x += right._x;
		_y += right._y;
		_z += right._z;
		return *this;
	}
	Vector& operator+(const Vector& right)
	{
		Vector temp(*this);//���Z���ʗp
		temp += right;
		return temp;
	}
	//Sub.
	Vector& operator-=(const Vector& right)
	{
		_x -= right._x;
		_y -= right._y;
		_z -= right._z;
		return *this;
	}
	Vector& operator-(const Vector& right)
	{
		Vector temp(*this);//���Z���ʗp
		temp -= right;
		return temp;
	}
};