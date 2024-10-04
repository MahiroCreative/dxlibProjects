#pragma once
#include <math.h>
using namespace std;

struct Vector3
{
	/*メンバ変数*/
	float X;
	float Y;
	float Z;

	/*メンバ関数*/
	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	float Length()
	{
		//三平方の定理
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/*演算子オーバーロード*/
	Vector3 operator+(const Vector3& right)
	{
		Vector3 ans;
		ans.X = this->X + right.X;
		ans.Y = this->Y + right.Y;
		ans.Z = this->Z + right.Z;
		return ans;
	}

};