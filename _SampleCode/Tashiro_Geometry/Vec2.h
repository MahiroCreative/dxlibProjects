#pragma once
#include <DxLib.h>

/// <summary>
/// �x�N�^�[2
/// </summary>
struct Vec2
{
public:
	float x;
	float y;
	
	Vec2();
	Vec2(float inX, float inY);

	/* ���Z */
	Vec2 operator-() const;
	Vec2 operator+(const Vec2& val) const;
	void operator+=(const Vec2& val);
	Vec2 operator-(const Vec2& val) const;
	void operator-=(const Vec2& val);
	Vec2 operator*(float scale) const;
	void operator*=(float scale);
	Vec2 operator/(float scale) const;
	void operator/=(float scale);
	bool operator==(const Vec2& val) const;
	bool operator!=(const Vec2& val) const;

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns></returns>
	float Length() const;
	/// <summary>
	/// ������2����擾
	/// </summary>
	/// <returns></returns>
	float SqLength() const;
	/// <summary>
	/// ���K�������x�N�g�����擾
	/// </summary>
	/// <returns></returns>
	Vec2 GetNormalized() const;
	/// <summary>
	/// ���g�̐��K��
	/// </summary>
	void Normalize();

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
float Dot(const Vec2& item1, const Vec2& item2);
/// <summary>
/// �O��
/// </summary>
/// <param name="item1">�x�N�g���P</param>
/// <param name="item2">�x�N�g���Q</param>
/// <returns>�O�ό���</returns>
float Cross(const Vec2& item1, const Vec2& item2);
/// <summary>
/// �ˉe
/// </summary>
/// <param name="projection">�ˉe����x�N�g��</param>
/// <param name="base">�ˉe��̕����ƂȂ�x�N�g��</param>
/// <returns>�ˉe�x�N�g��</returns>
Vec2 Projection(const Vec2& projection, const Vec2& base);
/// <summary>
/// ���������������Ă��邩(�덷���e)
/// </summary>
/// <param name="dir1">�����x�N�g���P</param>
/// <param name="dir2">�����x�N�g���Q</param>
/// <returns>true:�قړ��������������Ă���/ false:���������������Ă��Ȃ�</returns>
bool IsSameDirection(const Vec2& dir1, const Vec2& dir2);
