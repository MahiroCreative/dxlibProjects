#pragma once

// 1�N���X1�t�@�C����S�|����

// �Ȃ��킴�킴�N���X�̃����o��private�ɂ���́H
// ���ׂ�public�Ȃ�֗��ł́H

// const	�l��������Ȃ��悤�ɂ���
// �l�������ꂽ�����֗��@���ԈႦ�Ă����邱�Ƃ�h�����߂�const�ł�������������Ȃ��悤�ɂ���

// �E�N���X�̏����̓N���X���g�ɂ�点��
// �E�O���珟��ɒl���������Ȃ��悤�ɂ���
// ��D�G���\���ɂ����� ����ɉ�ʊO�̍��W�Ɉړ�������A�݂����Ȃ��Ƃ���������@���G�͐����Ă���͂��Ȃ̂ɉ�ʂɕ\������Ȃ��H�Ƃ������o�O

class Enemy
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^�͓���Ȏ������Ȃ�����public
	Enemy();
	~Enemy();

	// �N���X�O�Ŏg������(�����WinMain�Ŏg��)���̂�public
	void Init();
	//	void Update();
	void Draw();

	// �N���X�O���烁���o�ϐ���ύX�����ꍇ��public�ȃ����o�֐���ʂ�
	void SetPos(int x, int y);

	// �ȒP�Ȓ��g�Ȃ�w�b�_�ɒ��ڏ������Ƃ�����
	void SetPosX(int x) { m_posX = x; }
	void SetPosY(int y) { m_posX = y; }

private:
	// �����o�ϐ��͂��ׂ�private
	int m_handle;
	int m_posX;
	int m_posY;
};
