#pragma once
#include <DxLib.h>

/// <summary>
/// �x�N�^�[
/// </summary>
class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float inX, float inY, float inZ);
	Vec3(DxLib::VECTOR vec);
	static Vec3 Up();
	static Vec3 Down();
	static Vec3 Right();
	static Vec3 Left();
	static Vec3 Front();
	static Vec3 Back();
	static Vec3 Zero();

	/* ���Z */
	Vec3 operator+(const Vec3& val) const;
	void operator+=(const Vec3& val);
	Vec3 operator-(const Vec3& val) const;
	void operator-=(const Vec3& val);
	Vec3 operator*(float scale) const;
	void operator*=(float scale);
	Vec3 operator*(Vec3& val)const;
	Vec3 operator*(Vec3 val);
	void operator*=(Vec3& val);
	Vec3 operator/(float scale) const;
	void operator/=(float scale);
	bool operator==(const Vec3& val) const;
	bool operator!=(const Vec3& val) const;


	// �����擾
	float Length() const;
	// ������2����擾
	float SqLength() const;
	// ���K�������x�N�g�����擾
	Vec3 GetNormalized() const;
	// ���g�̐��K��
	void Normalize();

	// DxLib�p��VECTOR���擾
	DxLib::VECTOR VGet() const;

	void SetVECTOR(DxLib::VECTOR vec);
};

// ����
float Dot(const Vec3& item1, const Vec3& item2);
// �O��
Vec3 Cross(const Vec3& item1, const Vec3& item2);
// �ˉe
Vec3 Projection(const Vec3& projection, const Vec3& base);
