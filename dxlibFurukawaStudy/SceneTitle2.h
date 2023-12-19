#pragma once

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	static const int kBgNum = 4;

private:

	int m_bgHandle[4];	// bg -> background
	int m_bgNo;			// ���ݕ\�����Ă���BG�̔ԍ�
	// No	���݂̔ԍ�
	// Num	����


	int m_fadeCount;	// �t�F�[�h�x��		0:�����@�A�t�F�[�h�C�������������(�Q�[����ʂ������Ă���)
	//				�@255:�s�����A�t�F�[�h�A�E�g�����������(�^����)

	int m_fadeSpeed;	// �t�F�[�h�X�s�[�h
	int m_waitFrame;	// �t�F�[�h�C������������̑҂�����
};