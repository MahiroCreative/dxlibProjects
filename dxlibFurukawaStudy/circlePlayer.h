#pragma once
#include "circleEnemy.h"

class Player
{
public:
	Player();	// �쐬���ɌĂ΂��
	~Player();	// �폜���ɌĂ΂��

	void Init();	// ������
	void Update();	// ���t���[���̍X�V����
	void Draw() const;	// �`��
	void DrawPlayer() const;

	// �֐���const
	// �֐����Ń����o�[�ϐ��̒l��ύX�ł��Ȃ��Ȃ�
	int GetPosX() const { return m_posX; }		// �l�̓ǂݎ��:X���W
	int GetPosY() const { return m_posY; }		// �l�̓ǂݎ��:Y���W

	void Collision(Enemy& enemy, const int kEnemyNum);	// �����蔻��̊m�F

	bool isExist() const;

private:
	int m_posX;		// X���W
	int m_posY;		// Y���W
	int m_radius;	// ���a

	int m_hp;
	bool m_isHit;
};

void DrawHpBar(const int hp);