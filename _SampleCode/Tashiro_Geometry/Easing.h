#pragma once
#include <cmath>
#include <algorithm>
#include "Common/Game.h"
#include "Vec3.h"
#include "Quaternion.h"

enum class EasingType
{
	LERP,
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT,
	SLERP,
	MAX
};

/// <summary>
/// ���`���
/// </summary>
/// <typeparam name="T">�^</typeparam>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
template <typename T>
T Lerp(T start, T end, float t)
{
	return static_cast<T>(start + (end - start) * t);
}
/// <summary>
/// ���`���(�x�N�g��ver.)
/// </summary>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
Vec3 Lerp(const Vec3& start, const Vec3& end, float t);
/// <summary>
/// ���`��� 0�ɋ߂��قǓ�����������1�ɋ߂��قǓ������傫��
/// </summary>
/// <typeparam name="T">�^</typeparam>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
template <typename T>
T EaseIn(T start, T end, float t, float effect = 2.0f)
{
	float rate = std::powf(t, effect);
	return Lerp(start, end, rate);
}
/// <summary>
/// ���`��� 0�ɋ߂��قǓ�����������1�ɋ߂��قǓ������傫��(�x�N�g��ver.)
/// </summary>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
Vec3 EaseIn(const Vec3& start, const Vec3& end, float t, float effect = 2.0f);
/// <summary>
/// ���`��� 0�ɋ߂��قǓ������傫��1�ɋ߂��قǓ�����������
/// </summary>
/// <typeparam name="T">�^</typeparam>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
template <typename T>
T EaseOut(T start, T end, float t, float effect = 2.0f)
{
	float rate = 1.0f - std::powf(1.0f - t, effect);
	return Lerp(start, end, rate);
}
/// <summary>
/// ���`��� 0�ɋ߂��قǓ������傫��1�ɋ߂��قǓ�����������(�x�N�g��ver.)
/// </summary>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
Vec3 EaseOut(const Vec3& start, const Vec3& end, float t, float effect = 2.0f);
/// <summary>
/// ���`��� �^�񒆂����������������[���������傫��
/// </summary>
/// <typeparam name="T">�^</typeparam>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
template <typename T>
T EaseInOut(T start, T end, float t, float effect = 2.0f)
{
	float rate;
	if (t < 0.5f)
	{
		rate = 2 * (effect - 1.0f) * std::powf(t, effect);
	}
	else
	{
		rate = 1.0f - std::powf(-2 * t + 2, effect) * 0.5f;
	}
	return Lerp(start, end, rate);
}
/// <summary>
/// ���`��� �^�񒆂����������������[���������傫��(�x�N�g��ver.)
/// </summary>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">����</param>
/// <param name="effect">�e���x����</param>
/// <returns>�J�n�l�{�v�Z���ʒl</returns>
Vec3 EaseInOut(const Vec3& start, const Vec3& end, float t, float effect = 2.0f);

/// <summary>
/// ���ʐ��`���(�x�N�g��ver.)
/// </summary>
/// <param name="v1">�J�n�l</param>
/// <param name="v2">�I���l</param>
/// <param name="t">����</param>
/// <returns>�J�n�l���犄������]�����x�N�g��</returns>
Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
/// <summary>
/// ���ʐ��`���(�N�I�[�^�j�I��ver.)
/// </summary>
/// <param name="q1">�J�n�l</param>
/// <param name="q2">�I���l</param>
/// <param name="t">����</param>
/// <returns>�J�n�l���犄������]�����N�I�[�^�j�I��</returns>
Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);