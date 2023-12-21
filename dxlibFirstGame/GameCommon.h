#pragma once
#include "DxLib.h"
#include <math.h>

/// <summary>
/// ��ʃT�C�Y�Ȃǂ̋��ʒ萔
/// </summary>
namespace GameConst
{
	/*��ʃT�C�Y*/
	constexpr int ScreenSizeX = 1280;//��
	constexpr int ScreenSizeY = 720;//����
	/*���\�[�X�n���h��*/
	const int playerDrawHandle = LoadGraph("Resources/player.png");
}

struct Vector
{
public:
	/*�����o�ϐ�*/
	float X, Y, Z;

	/*�R���X�g���N�^*/
	Vector() :X(0.0f), Y(0.0f), Z(0.0f) {}//0�x�N�g��
	Vector(float x, float y) :X(x), Y(y), Z(0) {}//2�����x�N�g��
	Vector(float x, float y, float z) : X(x), Y(y), Z(z) {}//3�����x�N�g��

	/*�����o�֐�*/
	float Length()
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/*���Z�q�I�[�o�[���[�h*/
	//Add.
	Vector& operator+=(const Vector& right)
	{
		X += right.X;
		Y += right.Y;
		Z += right.Z;
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
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}
	Vector& operator-(const Vector& right)
	{
		Vector temp(*this);//���Z���ʗp
		temp -= right;
		return temp;
	}
	//Mult.
	Vector& operator*(const float& right)
	{
		Vector temp(*this);//���Z���ʗp
		temp.X = X * right;
		temp.Y = Y * right;
		temp.Z = Z * right;
		return temp;
	}
	//Div.
	Vector& operator/(const float& right)
	{
		Vector temp(*this);//���Z���ʗp
		temp.X = X / right;
		temp.Y = Y / right;
		temp.Z = Z / right;
		return temp;
	}
};