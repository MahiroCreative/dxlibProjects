#pragma once
#include <math.h>
using namespace std;

struct Vector3
{
	/*メンバ変数*/
	float X = 0;
	float Y = 0;
	float Z = 0;

	/*メンバ関数*/
	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	float Length()
	{
		//三平方の定理
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/*staticメンバ関数*/
	/// <summary>
	/// 内積の計算
	/// </summary>
	static float Dot(const Vector3& left,const Vector3& right)
	{

	}

	/*演算子オーバーロード*/
	//単項演算子
	Vector3 operator+(const Vector3& right)
	{
		Vector3 ans;
		ans.X = this->X + right.X;
		ans.Y = this->Y + right.Y;
		ans.Z = this->Z + right.Z;
		return ans;
	}
	Vector3 operator-(const Vector3& right)
	{
		Vector3 ans;
		ans.X = this->X - right.X;
		ans.Y = this->Y - right.Y;
		ans.Z = this->Z - right.Z;
		return ans;
	}
	Vector3 operator*(const float& right)
	{
		this->X = this->X * right;
		this->Y = this->Y * right;
		this->Z = this->Z * right;
	}
	Vector3 operator/(const float& right)
	{
		this->X = this->X / right;
		this->Y = this->Y / right;
		this->Z = this->Z / right;
	}
	void operator+=(const Vector3& right)
	{
		this->X += right.X;
		this->Y += right.Y;
		this->Z += right.Z;
	}
	void operator-=(const Vector3& right)
	{
		this->X -= right.X;
		this->Y -= right.Y;
		this->Z -= right.Z;
	}
	

};