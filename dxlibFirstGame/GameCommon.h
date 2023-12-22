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

struct IntVector
{
public:
	/*メンバ変数*/
	int X, Y, Z;

	/*コンストラクタ*/
	IntVector() :X(0), Y(0), Z(0) {}//0ベクトル
	IntVector(int x, int y) :X(x), Y(y), Z(0) {}//2次元ベクトル
	IntVector(int x, int y, int z) : X(x), Y(y), Z(z) {}//3次元ベクトル

	/*メンバ関数*/
	//ベクトルの大きさを出す(int型)
	int Length()
	{
		return (int)sqrt(X * X + Y * Y + Z * Z);
	}

	/*演算子オーバーロード*/
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
		IntVector temp(*this);//演算結果用
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
		IntVector temp(*this);//演算結果用
		temp -= right;
		return temp;
	}
	//Mult.
	IntVector& operator*(const int& right)
	{
		IntVector temp(*this);//演算結果用
		temp.X = X * right;
		temp.Y = Y * right;
		temp.Z = Z * right;
		return temp;
	}
	//Div.
	IntVector& operator/(const int& right)
	{
		IntVector temp(*this);//演算結果用
		temp.X = X / right;
		temp.Y = Y / right;
		temp.Z = Z / right;
		return temp;
	}
};