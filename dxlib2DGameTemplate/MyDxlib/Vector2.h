﻿#pragma once
//C++標準ライブラリ
#include <cmath>
#include <cassert>


struct Vector2
{
	/*メンバ変数*/
	float X = 0.0f;
	float Y = 0.0f;

	/*staticメンバ変数*/
	static const Vector2 Zero;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;

	/*メンバ関数*/
	//ベクトの長さ
	float Length() const;
	//ベクトルの長さの2乗(計算が早い)
	float LengthSq() const;
	//ベクトルの正規化
	Vector2 Normalize() const;

	/*staticメンバ関数*/
	//内積
	static float Dot(const Vector2& left, const Vector2& right);
};

/*staticメンバ変数の初期化*/
const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Down = Vector2(0.0f, -1.0f);

/*メンバ関数*/
float Vector2::Length() const
{
	return sqrtf(X * X + Y * Y);
}
float Vector2::LengthSq() const
{
	return X * X + Y * Y;
}
Vector2 Vector2::Normalize() const
{
	float len = Length();
	assert(len != 0, "0 division");//0除算
	return Vector2(X / len, Y / len);
}

/*staticメンバ関数*/
float Vector2::Dot(const Vector2& left, const Vector2& right)
{
	return left.X * right.X + left.Y * right.Y;
}


/*演算子オーバーロード*/
//A+B
Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return Vector2(left.X + right.X, left.Y + right.Y);
}
//A+=B
Vector2& operator+=(Vector2& left, const Vector2& right)
{
	left.X += right.X;
	left.Y += right.Y;
	return left;
}
//-A
Vector2 operator-(const Vector2& vec)
{
	return Vector2(-vec.X, -vec.Y);
}
//A-B
Vector2 operator-(const Vector2& left, const Vector2& right)
{
	return Vector2(left.X - right.X, left.Y - right.Y);
}
//A-=B
Vector2& operator-=(Vector2& left, const Vector2& right)
{
	left.X -= right.X;
	left.Y -= right.Y;
	return left;
}
//A*k(定数)
Vector2 operator*(const Vector2& vec, const float k)
{
	return Vector2(vec.X * k, vec.Y * k);
}
//k(定数)*A
Vector2 operator*(const float k, const Vector2& vec)
{
	return Vector2(vec.X * k, vec.Y * k);
}
//A*=k(定数)
Vector2& operator*=(Vector2& vec, const float k)
{
	vec.X *= k;
	vec.Y *= k;
	return vec;
}
//A/k(定数)
Vector2 operator/(const Vector2& vec, const float k)
{
	assert(k != 0, "0 division");//0除算
	return Vector2(vec.X / k, vec.Y / k);
}
//A/=k(定数)
Vector2& operator/=(Vector2& vec, const float k)
{
	assert(k != 0, "0 division");//0除算
	vec.X /= k;
	vec.Y /= k;
	return vec;
}