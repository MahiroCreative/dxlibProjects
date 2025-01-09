#pragma once
#include <DxLib.h>
#include "Vec2.h"

/// <summary>
/// �x�N�^�[3
/// </summary>
struct Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float inX, float inY, float inZ);
	Vec3(const Vec2& vec2);

	/// <summary>
	/// �E�x�N�g��
	/// </summary>
	/// <returns>(1, 0, 0)</returns>
	static Vec3 Right();
	/// <summary>
	/// ���x�N�g��
	/// </summary>
	/// <returns>(-1, 0, 0)</returns>
	static Vec3 Left();
	/// <summary>
	/// ��x�N�g��
	/// </summary>
	/// <returns>(0, 1, 0)</returns>
	static Vec3 Up();
	/// <summary>
	/// ���x�N�g��
	/// </summary>
	/// <returns>(0, -1, 0)</returns>
	static Vec3 Down();
	/// <summary>
	/// ���ʃx�N�g��
	/// </summary>
	/// <returns>(0, 0, 1)</returns>
	static Vec3 Front();
	/// <summary>
	/// �w�ʃx�N�g��
	/// </summary>
	/// <returns>(0, 0, -1)</returns>
	static Vec3 Back();

	/* ���Z */
	Vec3 operator-() const;
	Vec3 operator+(const Vec3& val) const;
	void operator+=(const Vec3& val);
	Vec3 operator-(const Vec3& val) const;
	void operator-=(const Vec3& val);
	Vec3 operator*(float scale) const;
	void operator*=(float scale);
	Vec3 operator/(float scale) const;
	void operator/=(float scale);
	bool operator==(const Vec3& val) const;
	bool operator!=(const Vec3& val) const;

	/// <summary>
	/// XZ�����݂̂��擾
	/// </summary>
	/// <returns>(x, z)</returns>
	Vec2 GetXZDir() const;

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>����</returns>
	float Length() const;
	/// <summary>
	/// ������2����擾
	/// </summary>
	/// <returns>������2��</returns>
	float SqLength() const;
	/// <summary>
	/// ���K�������x�N�g�����擾
	/// </summary>
	/// <returns>���K���x�N�g��</returns>
	Vec3 GetNormalized() const;
	/// <summary>
	/// ���g�̐��K��
	/// </summary>
	void Normalize();
	/// <summary>
	/// ���g�̐�Βl��
	/// </summary>
	void Abs();

	/// <summary>
	/// DxLib�p��VECTOR���擾
	/// </summary>
	/// <returns>DxLib::VECTOR</returns>
	DxLib::VECTOR VGet() const;
};

/// <summary>
/// ����
/// </summary>
/// <param name="item1">�x�N�g���P</param>
/// <param name="item2">�x�N�g���Q</param>
/// <returns>���ό���</returns>
float Dot(const Vec3& item1, const Vec3& item2);
/// <summary>
/// �O��
/// </summary>
/// <param name="item1">�x�N�g���P</param>
/// <param name="item2">�x�N�g���Q</param>
/// <returns>�O�ό���</returns>
Vec3 Cross(const Vec3& item1, const Vec3& item2);
/// <summary>
/// �ˉe
/// </summary>
/// <param name="projection">�ˉe����x�N�g��</param>
/// <param name="base">�ˉe��̕����ƂȂ�x�N�g��</param>
/// <returns>�ˉe�x�N�g��</returns>
Vec3 Projection(const Vec3& projection, const Vec3& base);
/// <summary>
/// ����
/// </summary>
/// <param name="vec">���˂�����x�N�g��</param>
/// <param name="norm">�@���x�N�g��</param>
/// <returns>���ˌ�̃x�N�g��</returns>
Vec3 Reflection(const Vec3& vec, const Vec3& norm);
/// <summary>
/// ���������������Ă��邩(�덷���e)
/// </summary>
/// <param name="dir1">�����x�N�g���P</param>
/// <param name="dir2">�����x�N�g���Q</param>
/// <returns>true:�قړ��������������Ă���/ false:���������������Ă��Ȃ�</returns>
bool IsSameDirection(const Vec3& dir1, const Vec3& dir2);
/// <summary>
/// ���������������Ă��邩(180�x����)
/// </summary>
/// <param name="dir1">�����x�N�g���P</param>
/// <param name="dir2">�����x�N�g���Q</param>
/// <returns>true:2�̃x�N�g���̓��ό��ʂ�180�x����/ false:���ό��ʂ�180�x�ȏ�</returns>
bool IsUniformDirection(const Vec3& dir1, const Vec3& dir2);