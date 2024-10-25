#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Vec3.h"

struct Quaternion;

/// <summary>
/// 4x4�s��
/// </summary>
struct Matrix4x4
{
public:
	float m[4][4];
	// �s->��

	Matrix4x4();

	/* ���Z */
	Matrix4x4 operator+ (const Matrix4x4& mat) const;
	Matrix4x4 operator- (const Matrix4x4& mat) const;
	Matrix4x4 operator* (const Matrix4x4& mat) const;
	Matrix4x4 operator/ (float div) const;

	/// <summary>
	/// �S�l��0�ɂ���
	/// </summary>
	void Zero();
	/// <summary>
	/// �P�ʍs��ɂ���
	/// </summary>
	void Identity();
	/// <summary>
	/// �]�u�s���Ԃ�
	/// </summary>
	/// <returns>�]�u�s��</returns>
	Matrix4x4 Transpose();
	/// <summary>
	/// �t�s���Ԃ�
	/// </summary>
	/// <param name="isCorrect">true:���m�Ȍ��ʂ�Ԃ����v�Z���d�� /false:�ȈՓI�Ȍ��ʂ�Ԃ����v�Z���y��</param>
	/// <returns>�t�s��</returns>
	Matrix4x4 Inverse(bool isCorrect = false);

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>���W</returns>
	Vec3 GetPos() const;
	/// <summary>
	/// ��]�s����N�I�[�^�j�I���ɂ��ĕԂ�
	/// </summary>
	/// <returns>��]</returns>
	Quaternion GetRot() const;

	/// <summary>
	/// DxLib�p�̍s���Ԃ�
	/// </summary>
	/// <returns>DxLib::MATRIX</returns>
	MATRIX GetMATRIX() const;

private:
	/// <summary>
	/// ���ӂ̗�ƉE�ӂ̍s���v�Z����
	/// </summary>
	/// <param name="mat">�E�ӑ��̍s��</param>
	/// <param name="line">��</param>
	/// <param name="row">�s</param>
	/// <returns>�v�Z�����l</returns>
	float Dot(const Matrix4x4& mat, int line, int row) const;
};

/// <summary>
/// �x�N�g�����X�P�[���ɂ����s���Ԃ�
/// </summary>
/// <param name="size">�X�P�[��</param>
/// <returns>�X�P�[���ɒl���������s��</returns>
Matrix4x4 Scale(const Vec3& size);
/// <summary>
/// �x�N�g�������W�ɂ����s���Ԃ�
/// </summary>
/// <param name="pos">���W</param>
/// <returns>���W���������s��</returns>
Matrix4x4 Pos(const Vec3& pos);
/// <summary>
/// �N�I�[�^�j�I������]�s��ɂ��ĕԂ�
/// </summary>
/// <param name="q">�N�I�[�^�j�I��(��])</param>
/// <returns>��]�s��</returns>
Matrix4x4 Rot(const Quaternion& q);
