#pragma once
#include "DxLib.h"
#include <math.h>

/// <summary>
/// 画面サイズなどの共通定数
/// </summary>
namespace GameConst
{
	/*画面サイズ*/
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ
	/*リソースハンドル*/
	const int playerDrawHandle = LoadGraph("Resources/player.png");
}

struct Vector
{
public:
	/*メンバ変数*/
	float X, Y, Z;

	/*コンストラクタ*/
	Vector() :X(0.0f), Y(0.0f), Z(0.0f) {}//0ベクトル
	Vector(float x, float y) :X(x), Y(y), Z(0) {}//2次元ベクトル
	Vector(float x, float y, float z) : X(x), Y(y), Z(z) {}//3次元ベクトル

	/*メンバ関数*/
	float Length()
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/*演算子オーバーロード*/
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
		Vector temp(*this);//演算結果用
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
		Vector temp(*this);//演算結果用
		temp -= right;
		return temp;
	}
	//Mult.
	Vector& operator*(const float& right)
	{
		Vector temp(*this);//演算結果用
		temp.X = X * right;
		temp.Y = Y * right;
		temp.Z = Z * right;
		return temp;
	}
	//Div.
	Vector& operator/(const float& right)
	{
		Vector temp(*this);//演算結果用
		temp.X = X / right;
		temp.Y = Y / right;
		temp.Z = Z / right;
		return temp;
	}
};