#pragma once
#include "DxLib.h"
#include <math.h>

/*���w�n*/
/// <summary>
/// �y���[�U��`�z�y�ˑ�:�����z
/// int�����̃x�N�^�[�^.
/// </summary>
struct IntVector
{
public:
	/*�����o�ϐ�*/
	int X, Y, Z;

	/*�R���X�g���N�^*/
	IntVector() :X(0), Y(0), Z(0) {}//0�x�N�g��
	IntVector(int x, int y) :X(x), Y(y), Z(0) {}//2�����x�N�g��
	IntVector(int x, int y, int z) : X(x), Y(y), Z(z) {}//3�����x�N�g��

	/*�����o�֐�*/
	//�x�N�g���̑傫�����o��(int�^)
	int Length()
	{
		return (int)sqrt(X * X + Y * Y + Z * Z);
	}

	/*���Z�q�I�[�o�[���[�h*/
	//Add.
	IntVector& operator+=(const IntVector& right)
	{
		X += right.X;
		Y += right.Y;
		Z += right.Z;
		return *this;
	}
	IntVector& operator+(const IntVector& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp += right;
		return temp;
	}
	//Sub.
	IntVector& operator-=(const IntVector& right)
	{
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}
	IntVector& operator-(const IntVector& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp -= right;
		return temp;
	}
	//Mult.
	IntVector& operator*(const int& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp.X = X * right;
		temp.Y = Y * right;
		temp.Z = Z * right;
		return temp;
	}
	//Div.
	IntVector& operator/(const int& right)
	{
		IntVector temp(*this);//���Z���ʗp
		temp.X = X / right;
		temp.Y = Y / right;
		temp.Z = Z / right;
		return temp;
	}
};

/*���o�͌n*/
/// <summary>
/// �y���[�U��`:static�z�y�ˑ�:Dxlib�z
/// </summary>
class MyKeyInput
{
private:
	/*static�����o�ϐ�*/
	//���ꂼ���Key�̓��̓t���[����
	static int KeyFrame[];//��`�����s�����Ԃ͏�Ő����B
public:
	MyKeyInput() {}
	/*static�����o�֐�*/
	/// <summary>
	/// Key�̓��͏�Ԃ̍X�V�B
	/// ���t���[�����ƂɎ��s���邱�ƂōX�V����B
	/// </summary>
	static void Update()
	{
		// ���݂̃L�[�̓��͏��
		char tmpKey[256];
		// �S�ẴL�[�̓��͏�Ԃ��擾
		GetHitKeyStateAll(tmpKey);
		//�S�Ă�Key�̓��͏�Ԃ̊m�F
		for (int i = 0; i < 256; i++)
		{
			//i�Ԃ�Key��������Ă��邩�𔻒�
			if (tmpKey[i] != 0)
			{
				//�����Ă���Key�̃t���[�������Z
				KeyFrame[i]++;
			}
			else
			{
				//������Ă��Ȃ�Key�̃t���[����������
				KeyFrame[i] = 0;
			}
		}
	}
	/// <summary>
	/// Key�������ꂽ�u�Ԃ��擾����B
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <param name="KeyCode">Dxlib��KeyCode</param>
	static bool isDownKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] == 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Key�������ꑱ���Ă��邩���擾����B
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <param name="KeyCode">Dxlib��KeyCode</param>
	static bool isHoldKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Key��������Ă���t���[�������擾����
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <returns>Dxlib��KeyCode</returns>
	static int HoldKeyTime(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return KeyFrame[KeyCode];
		}
		return 0;
	}
};
//�ÓI�����o�ϐ��̎��ԍ쐬
int MyKeyInput::KeyFrame[256];