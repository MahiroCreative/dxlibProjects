#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;

	// �O���t�B�b�N�̎w��
	void SetGraphHandle(int handle);

	// �G�L�����N�^�[�̊J�n����
	// ��ʏォ�痎���n�߂�
	void Start();

	// ���݂��邩�`�F�b�N
	bool IsExist() const { return m_isExist; }

	// �G�L�����N�^�[�̏����ʒu�ݒ�
	void SetStartPos();

	float GetLeft() const { return m_posX[0]; }
	float GetRight() const { return m_posX[0] + m_graphWidth; }
	float GetUp() const { return m_posY[0]; }
	float GetDown() const { return m_posY[0] + m_graphHeight; }

private:
	// �c���p�ɕۑ�����ʒu���̐�
	static constexpr int kPosLogFrame = 8;

private:
	int m_handle;
	int m_graphWidth;
	int m_graphHeight;

	// ���݂��邩
	bool m_isExist;

	// �ʒu���
	float m_posX[kPosLogFrame];
	float m_posY[kPosLogFrame];

	// �ړ���
	float m_moveY;
};