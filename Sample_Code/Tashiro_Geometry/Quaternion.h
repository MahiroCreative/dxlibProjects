#pragma once
#include "Vec3.h"

/// <summary>
/// �N�I�[�^�j�I��
/// </summary>
struct Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);

	/// <summary>
	/// �����N�I�[�^�j�I��
	/// </summary>
	/// <returns>�����N�I�[�^�j�I��</returns>
	Quaternion Conjugated() const;

	/* ���Z�q�I�[�o�[���[�h */
	Quaternion operator* (const Quaternion& q) const;
	Vec3 operator* (const Vec3& vec) const;

	/// <summary>
	/// �N�I�[�^�j�I����X,Y,Z�ɂǂꂭ�炢��]���Ă��邩�ɂ��ĕԂ�
	/// </summary>
	/// <returns>�ʓx�@�ł̉�]�</returns>
	Vec3 GetRadian() const;
};

/// <summary>
/// ������ɉ�]������N�I�[�^�j�I�����쐬
/// </summary>
/// <param name="angle">��]�x����(�x���@)</param>
/// <param name="axis">��</param>
/// <returns>�N�I�[�^�j�I��</returns>
Quaternion AngleAxis(float angle, const Vec3& axis);
/// <summary>
/// �N�I�[�^�j�I�����m�̓���
/// </summary>
/// <param name="q1">�E��</param>
/// <param name="q2">����</param>
/// <returns>����</returns>
float Dot(const Quaternion& q1, const Quaternion& q2);

