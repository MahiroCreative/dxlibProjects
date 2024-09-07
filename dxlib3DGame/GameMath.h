#pragma once
#include<math.h>
using namespace std;

/// <summary>
/// 3次元ベクトル用の構造体
/// </summary>
struct Vector3 {
	/*メンバ変数*/
	//X座標(第1成分)
	float X;
	//Y座標(第2成分)
	float Y;
	//Z座標(第3成分)
	float Z;

	/*メンバ関数*/
	//ベクトルの長さを取得
	float Length()
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}

	/*演算子オーバーロード*/
	//単項演算子(+)
	Vector3 operator+(const Vector3& temp)
	{

	}

};

