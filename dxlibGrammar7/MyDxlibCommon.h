#pragma once
#include "Dxlib.h"

namespace WindowSize
{
	constexpr int SIZE_X = 1280;//��ʃT�C�YX
	constexpr int SIZE_Y = 720;//��ʃT�C�YY
}

namespace ColorCode
{
	//�v���O�������s�����܂�萔��const.
	//���̏ꍇ����GetColor�֐��Ōv�Z����Ă��猈�܂�̂�const.
	const unsigned int BLACK = GetColor(0, 0, 0);//��
	const unsigned int RED = GetColor(255, 0, 0);//��
	const unsigned int LIME = GetColor(0, 255, 0);//���C��
	const unsigned int BLUE = GetColor(0, 0, 255);//��
	const unsigned int YELLOW = GetColor(255, 255, 0);//��
	const unsigned int AQUA = GetColor(0, 255, 255);//�A�N�A
	const unsigned int MAGENTA = GetColor(255, 0, 255);//�}�[���^
}



/*InputKey*/
//KeyInputFlag.�L�[�C���v�b�g�p�̃t���O�\����.
// KeyCode��int�Ŏ��B
struct IsKeyInput
{
	bool IsNow = false;//�����ꂽ�u��True
	bool IsHold = false;//������Ă���Œ�True
	int KeyCode;//�L�[�R�[�h
};
/// <summary>
/// �������ŃL�[�t���O��n���A�X�V�������œ���.
/// �Q�[�����[�v���ɖ��t���[�����s���邱�ƂŊm�F���Ă���B
/// Enter/Up/Down/Left/Right�@�̓��͂��擾����B
/// </summary>
/// <param name="_keyFlag">���g�ō쐬�����L�[�t���O</param>
/// <returns></returns>
IsKeyInput InputKeyUpdate(IsKeyInput _keyFlag)
{
	//EnterKey.
	if (CheckHitKey(_keyFlag.KeyCode) && !_keyFlag.IsHold)//�����ꂽ���A�����ꑱ���Ă��Ȃ��B
	{
		//�����ꂽ�u��
		_keyFlag.IsNow = true;
		_keyFlag.IsHold = true;
	}
	else if (CheckHitKey(_keyFlag.KeyCode) && _keyFlag.IsHold)//�����ꂽ���A�����ꑱ���Ă���.
	{
		//�����ꑱ���Ă���
		_keyFlag.IsNow = false;
		_keyFlag.IsHold = true;
	}
	else//������Ă��Ȃ��B
	{
		_keyFlag.IsNow = false;
		_keyFlag.IsHold = false;
	}

	return _keyFlag;
}