#pragma once

class Enemy
{
public:
	Enemy();	// �R���X�g���N�^
	~Enemy();	// �f�X�g���N�^

	void Init();					// ������
	void Update();						// ���t���[���̍X�V
	void Draw();			// �`��
	void SetPosX(int x);
	int GetPosX() const { return m_posX; }		// �l�̓ǂݎ��:X���W
	int GetPosY() const { return m_posY; }		// �l�̓ǂݎ��:Y���W
	int GetMoveX() const { return m_moveX; }		// �l�̓ǂݎ��:Y���W
	int GetMoveY() const { return m_moveY; }		// �l�̓ǂݎ��:Y���W
	int GetRadius() const { return m_radius; }	// �l�̓ǂݎ��:���a

	bool GetIsHit() const { return m_isHit; }
	void ChangIsHit() { m_isHit = !m_isHit; }

	int GetChangTime() const { return m_changTime; }
	int GetDelayChangTime() const;

private:
	int m_posX;		// X���W
	int m_posY;		// Y���W
	int m_radius;	// ���a
	bool m_isHit;
	int m_moveX;
	int m_moveY;

	int m_changTime;
};
