#pragma once
#include "Vec3.h"
#include <cmath>
#include <cassert>

/// <summary>
/// クオータニオン
/// </summary>
struct Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion() :
		x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{}
	Quaternion(float inX, float inY, float inZ, float inW) :
		x(inX), y(inY), z(inZ), w(inW)
	{}

	/// <summary>
	/// 共役クオータニオン
	/// </summary>
	/// <returns>共役クオータニオン</returns>
	Quaternion Conjugated() const { return Quaternion(-x, -y, -z, w); }

	/* 演算子オーバーロード */
	Quaternion operator* (const Quaternion& q) const
	{
		Quaternion res;

		res.x = x * q.w + w * q.x - z * q.y + y * q.z;
		res.y = y * q.w + z * q.x + w * q.y - x * q.z;
		res.z = z * q.w - y * q.x + x * q.y + w * q.z;
		res.w = w * q.w - x * q.x - y * q.y - z * q.z;

		return res;
	}
	Vec3 operator* (const Vec3& vec) const
	{
		Quaternion posQ = Quaternion(vec.x, vec.y, vec.z, 1.0f);

		Quaternion newPos = *this * posQ * this->Conjugated();

		return Vec3(newPos.x, newPos.y, newPos.z);
	}

	/// <summary>
	/// クオータニオンをX,Y,Zにどれくらい回転しているかにして返す
	/// </summary>
	/// <returns>弧度法での回転具合</returns>
	Vec3 GetRadian() const
	{
		float q00 = w * w;
		float q11 = x * x;
		float q22 = y * y;
		float q33 = z * z;
		float q01 = w * x;
		float q02 = w * y;
		float q03 = w * z;
		float q12 = x * y;
		float q13 = x * z;
		float q23 = y * z;

		Vec3 res;

		res.x = std::atan2f(2.0f * (q23 + q01), (q00 - q11 - q22 + q33));
		res.y = -std::asinf(2.0f * (q13 - q02));
		res.z = std::atan2f(2.0f * (q12 + q03), (q00 + q11 - q22 - q33));

		return res;
	}

public:
	/// <summary>
	/// クオータニオン同士の内積
	/// </summary>
	/// <param name="q1">右辺</param>
	/// <param name="q2">左辺</param>
	/// <returns>内積</returns>
	static float Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}
	/// <summary>
	/// 軸を基準に回転させるクオータニオンを作成
	/// </summary>
	/// <param name="angle">回転度合い(度数法)</param>
	/// <param name="axis">軸</param>
	/// <returns>クオータニオン</returns>
	static Quaternion AngleAxis(float angle, const Vec3& axis)
	{
		Quaternion result;

		float halfRad = angle * Game::DEG_2_RAD * 0.5f;
		float sin = std::sin(halfRad);
		float cos = std::cos(halfRad);
		auto normAxis = axis.GetNormalized();
		assert(normAxis.SqLength() > 0.0f && "軸がありません");

		result = Quaternion(normAxis.x * sin, normAxis.y * sin, normAxis.z * sin, cos);

		return result;
	}
	/// <summary>
	/// 2つのベクトル間のクオータニオンを取得する
	/// </summary>
	/// <param name="v1">ベクトル１</param>
	/// <param name="v2">ベクトル２</param>
	/// <param name="axisWhenParallel">2ベクトル間が平行の場合の軸</param>
	/// <returns>クオータニオン</returns>
	static Quaternion GetQuaternion(const Vec3& v1, const Vec3& v2, const Vec3& axisWhenParallel = Vec3::Up())
	{
		auto norm1 = v1.GetNormalized();
		auto norm2 = v2.GetNormalized();
		float dot = Vec3::Dot(norm1, norm2);
		float angle = std::acosf(dot) * Game::RAD_2_DEG;
		auto axis = Vec3::Cross(norm1, norm2);
		if (axis.SqLength() == 0.0f)
		{
			axis = axisWhenParallel;
		}

		return AngleAxis(angle, axis);
	}
};

