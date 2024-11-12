///外部ライブラリに依存しない数学系ライブラリ
#pragma once
#include <cassert>
#include <string>
#include <cmath>
#include <numbers>
#include "Vector3.h"

using namespace std;

/*Vector3*/
/// <summary>
/// Vector3型の構造体
/// </summary>
struct Vector3
{
	/*メンバ変数*/
	float X = 0, Y = 0, Z = 0;

	/*演算子オーバーロード*/
	//単項演算子(const付けるとメンバ変数の変更を行えなくなる)
	Vector3 operator+(const Vector3& right) const
	{
		Vector3 ans;
		ans.X = this->X + right.X;
		ans.Y = this->Y + right.Y;
		ans.Z = this->Z + right.Z;
		return ans;
	}
	Vector3 operator-(const Vector3& right) const
	{
		Vector3 ans;
		ans.X = this->X - right.X;
		ans.Y = this->Y - right.Y;
		ans.Z = this->Z - right.Z;
		return ans;
	}
	Vector3 operator*(const float& right) const
	{
		Vector3 ans;
		ans.X = this->X * right;
		ans.Y = this->Y * right;
		ans.Z = this->Z * right;
		return ans;
	}
	Vector3 operator/(const float& right) const
	{
		assert(right != 0.0f && "0で除算しています！");
		//実処理
		Vector3 ans;
		ans.X = this->X / right;
		ans.Y = this->Y / right;
		ans.Z = this->Z / right;
		return ans;
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

	/*メンバ関数*/
	/// <summary>
	/// ベクトル成分の一括代入
	/// </summary>
	void Set(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
	}
	/// <summary>
	/// ベクトルの大きさを取得
	/// </summary>
	float Magnitude() const
	{
		//平方和の平方根(2乗して足した後にルートする)
		return hypot(this->X, this->Y, this->Z);
	}
	/// <summary>
	/// ベクトルの大きさの2乗を取得(ルートしてないので早い)
	/// </summary>
	float sqrtMagnitude() const
	{
		return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
	}
	/// <summary>
	/// 正規化したベクトルを取得
	/// </summary>
	Vector3 Normalize() const
	{
		Vector3 ans;
		//正規化
		ans = (*this) / this->Magnitude();
		return ans;
	}
	/// <summary>
	/// 全ての成分の絶対値を取ったベクトルを取得
	/// </summary>
	Vector3 Abs()
	{
		Vector3 ans;
		//絶対値の計算
		ans.X = abs(this->X);
		ans.Y = abs(this->Y);
		ans.Z = abs(this->Z);
		return ans;
	}
	/// <summary>
	/// ベクトル成分を文字列で返す
	/// </summary>
	string ToString() const
	{
		return to_string(X) + ":" + to_string(Y) + ":" + to_string(Z);
	}

	/*staticメンバ関数*/
	/// <summary>
	/// 内積の計算
	/// </summary>
	static float Dot(const Vector3& left, const Vector3& right)
	{
		//変数
		float ans;
		//計算
		ans = left.X * right.X + left.Y * right.Y + left.Z * right.Z;
		//return
		return ans;
	}
	/// <summary>
	/// 外積の計算
	/// </summary>
	static Vector3 Cross(const Vector3& left, const Vector3& right)
	{
		//変数
		Vector3 ans;
		//計算
		ans.X = left.Y * right.Z - left.Z * right.Y;
		ans.Y = left.Z * right.X - left.X * right.Z;
		ans.Z = left.X * right.Y - left.Y * right.X;
		//return
		return ans;
	}

};

/// <summary>
/// Vector3型の定数(よく使うもの)
/// </summary>
namespace kVector3
{
	constexpr Vector3 ZERO{ 0,0,0 };
	constexpr Vector3 UP{ 0,1,0 };
	constexpr Vector3 DOWN{ 0,1,0 };
	constexpr Vector3 Right{ 1,0,0 };
	constexpr Vector3 LEFT{ -1,0,0 };
	constexpr Vector3 FOWARD{ 0,0,1 };
	constexpr Vector3 BACK{ 0,0,-1 };
}

/*Quaternion*/
/// <summary>
/// Quaternion型の構造体
/// </summary>
struct Quaternion
{
	//実部,虚部X,虚部Y,虚部Z
	float X = 0, Y = 0, Z = 0, W = 1.0f;

	/*演算子オーバーロード*/
	/// <summary>
	/// クォータニオン同士の掛け算(回転の合成)
	/// </summary>
	Quaternion operator*(const Quaternion& right) const
	{
		Quaternion ans;

		//計算(クォータニオンの掛け算)
		ans.X = this->W * right.X + this->X * right.W + this->Y * right.Z - this->Z * right.Y;
		ans.Y = this->W * right.Y - this->X * right.Z + this->Y * right.W + this->Z * right.X;
		ans.Z = this->W * right.Z + this->X * right.Y - this->Y * right.X + this->Z * right.W;
		ans.W = this->W * right.W - this->X * right.X - this->Y * right.Y - this->Z * right.Z;

		//return
		return ans;
	}
	/// <summary>
	/// クォータニオンとベクトルの掛け算。回転後のベクトルを返す。
	/// (計算としてはqpq*であり、クォータニオンと共役クォータニオンでベクトルを挟んでる)
	/// </summary>
	Vector3 operator*(const Vector3& right) const
	{
		//３次元ベクトルをクォータニオンに変換
		Quaternion q{ right.X,right.Y,right.Z,1.0f };

		//回転クォータニオンのインバースの作成
		//逆クォータニオンを出すのは大変なので、
		//3次元だと同じ値になる共役クオータニオンで作成(虚部だけマイナス反転)
		Quaternion qInv{ -this->X, -this->Y, -this->Z,this->W };

		//回転後のクォータニオンの作成
		Quaternion qRes = (*this) * q * qInv;

		//3次元座標に変換
		Vector3 ans{ qRes.X, qRes.Y, qRes.Z };

		//return.
		return ans;
	}

	/*メンバ関数*/
	/// <summary>
	/// クォータニオンの成分をセット。
	/// </summary>
	void Set(float x, float y, float z, float w) { this->X = x; this->Y = y; this->Z = z; this->W = w; }
	/// <summary>
	/// 逆クォータニオンを返す。ただし、三次元なので共役を出してるだけ。
	/// (虚部だけマイナスにする)
	/// </summary>
	Quaternion Inverse() const { return Quaternion{ this->W,-this->X,-this->Y,-this->Z }; }
	/// <summary>
	/// オイラー角に変換。
	/// </summary>
	/// <returns>オイラー角(Vector3)</returns>
	Vector3 GetEulerAngle() const
	{
		//変数
		Vector3 ans;
		//計算
		ans.X = atan2(2 * (this->W * this->X + this->Y * this->Z), 1 - 2 * (this->X * this->X + this->Y * this->Y));
		ans.Y = asin(2 * (this->W * this->Y - this->Z * this->X));
		ans.Z = atan2(2 * (this->W * this->Z + this->X * this->Y), 1 - 2 * (this->Y * this->Y + this->Z * this->Z));
		//return
		return ans;
	}
	/// <summary>
	/// 成分を文字列にして返す.
	/// </summary>
	string ToString() const
	{
		return to_string(X) + ":" + to_string(Y) + ":" + to_string(Z) + ":" + to_string(W);
	}

	/*staticメンバ関数*/
	/// <summary>
	/// オイラー角からクォータニオンを作成
	/// (XYZ系)
	/// </summary>
	/// <param name="angle">オイラー角(Vector3)</param>
	static Quaternion Euler(Vector3 angle)
	{
		//度数からラジアンに変換
		angle.X = angle.X * numbers::pi_v<float> / 180.0f;
		angle.Y = angle.Y * numbers::pi_v<float> / 180.0f;
		angle.Z = angle.Z * numbers::pi_v<float> / 180.0f;

		//要素計算
		float cosX = cos(angle.X / 2);
		float sinX = sin(angle.X / 2);
		float cosY = cos(angle.Y / 2);
		float sinY = sin(angle.Y / 2);
		float cosZ = cos(angle.Z / 2);
		float sinZ = sin(angle.Z / 2);

		//クォータニオンの作成
		Quaternion ans;
		ans.W = cosX * cosY * cosZ + sinX * sinY * sinZ;
		ans.X = sinX * cosY * cosZ - cosX * sinY * sinZ;
		ans.Y = cosX * sinY * cosZ + sinX * cosY * sinZ;
		ans.Z = cosX * cosY * sinZ - sinX * sinY * cosZ;

		//return
		return ans;
	}
	/// <summary>
	/// クオータニオンの内積
	/// </summary>
	static float Dot(const Quaternion& left, const Quaternion& right)
	{
		return left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
	}
	/// <summary>
	/// 軸を基準に回転させるクオータニオンを作成.
	/// </summary>
	/// <param name="angle">回転度合い(度数法)</param>
	/// <param name="axis">軸(Vector3)</param>
	/// <returns>クオータニオン</returns>
	static Quaternion AngleAxis(float angle, const Vector3& axis)
	{
		//度数からラジアンに変換
		float Rad = angle * numbers::pi_v<float> / 180.0f;

		//回転軸の正規化
		Vector3 nAxis = axis.Normalize();
		//存在しうる軸かを確認.
		assert(nAxis.sqrtMagnitude() > 0.0f && "軸がありません");

		//回転クォータニオンの作成
		//(w:実部 , ijk:虚部 とする)
		//n: ijk軸上の単位ベクトル(軸となるベクトル)
		//q = w cos(θ/2) + n sin(θ/2)
		Quaternion ans;
		ans.W = cos(Rad / 2);
		ans.X = nAxis.X * sin(Rad / 2);
		ans.Y = nAxis.Y * sin(Rad / 2);
		ans.Z = nAxis.Z * sin(Rad / 2);

		//return
		return ans;
	}
};

