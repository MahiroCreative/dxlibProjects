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

struct IntVector
{
public:
	/*�����o�ϐ�*/
	int X, Y, Z;

	/*�R���X�g���N�^*/
	IntVector() :X(0), Y(0), Z(0) {}//0�x�N�g��
	IntVector(int x, int y) :X(x), Y(y), Z(0) {}//2�����x�N�g��
	IntVector(int x, int y, int z) : X(x), Y(y), Z(z) {}//3�����x�N�g��

	/*�����o�֐�*/
	//�x�N�g���̑傫�����o��(int�^)
	int Length()
	{
		return (int)sqrt(X * X + Y * Y + Z * Z);
	}

	/*���Z�q�I�[�o�[���[�h*/
	//Add.
	IntVector& operator+=(const IntVector& right)
	{
		X += right.X;
		Y += right.Y;
		Z += right.Z;
		return *this;
	}
	IntVector& operator+(const IntVector& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp += right;
		return temp;
	}
	//Sub.
	IntVector& operator-=(const IntVector& right)
	{
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}
	IntVector& operator-(const IntVector& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp -= right;
		return temp;
	}
	//Mult.
	IntVector& operator*(const int& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp.X = X * right;
		temp.Y = Y * right;
		temp.Z = Z * right;
		return temp;
	}
	//Div.
	IntVector& operator/(const int& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp.X = X / right;
		temp.Y = Y / right;
		temp.Z = Z / right;
		return temp;
	}
};