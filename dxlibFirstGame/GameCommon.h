#pragma once
#include "DxLib.h"

/// <summary>
/// 画面サイズなどの共通定数
/// </summary>
namespace GameConst
{
	/*画面サイズ*/
	constexpr int ScreenSizeX = 1280;//幅
	constexpr int ScreenSizeY = 720;//高さ
	/*リソースハンドル*/
	const int playerDrawHandle = LoadGraph("Resources\player.png");
}

struct Vector
{
public:
	/*メンバ変数*/
	int _x,_y,_z;

	/*コンストラクタ*/
	Vector():_x(0),_y(0),_z(0){}//0ベクトル
	Vector(int x, int y) :_x(x), _y(y), _z(0) {}//2次元ベクトル
	Vector(int x, int y, int z) : _x(x), _y(y), _z(z) {}//3次元ベクトル

	/*演算子オーバーロード*/
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
		Vector temp(*this);//演算結果用
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
		Vector temp(*this);//演算結果用
		temp -= right;
		return temp;
	}
};