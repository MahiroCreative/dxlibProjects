#pragma once
#include<math.h>
using namespace std;

/// <summary>
/// 3次元ベクトル用の構造体
/// </summary>
struct Vector3 {
	/*メンバ変数*/
	//X座標(第1成分)
	float X = 0;
	//Y座標(第2成分)
	float Y = 0;
	//Z座標(第3成分)
	float Z = 0;

	/*メンバ関数*/
	//ベクトルの長さを取得
	float Length()
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/*演算子オーバーロード*/
	//+
	Vector3 operator+(const Vector3& right)
	{
		Vector3 ans;
		ans.X = X + right.X;
		ans.Y = Y + right.Y;
		ans.Z = Z + right.Z;
		return ans;
	}
	//-
	Vector3 operator-(const Vector3& right)
	{
		Vector3 ans;
		ans.X = X - right.X;
		ans.Y = Y - right.Y;
		ans.Z = Z - right.Z;
		return ans;
	}
	//+=
	Vector3& operator+=(const Vector3& right)
	{
		X += right.X;
		Y += right.Y;
		Z += right.Z;
		return *this;
	}
	//-=
	Vector3& operator-=(const Vector3& right)
	{
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}

};

