#pragma once
#include<math.h>
using namespace std;

/// <summary>
/// 3�����x�N�g���p�̍\����
/// </summary>
struct Vector3 {
	/*�����o�ϐ�*/
	//X���W(��1����)
	float X;
	//Y���W(��2����)
	float Y;
	//Z���W(��3����)
	float Z;

	/*�����o�֐�*/
	//�x�N�g���̒������擾
	float Length()
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}

	/*���Z�q�I�[�o�[���[�h*/
	//�P�����Z�q(+)
	Vector3 operator+(const Vector3& temp)
	{

	}

};

