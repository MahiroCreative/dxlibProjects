#pragma once
#include "Enemy.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw() const;

	void SetGraphHandle(int handle);
	void SetStartPos();
	void SetWalkSeHandle(int handle) { m_walkSe = handle; }


	// �����蔻��
	bool IsCollision(const Enemy& enemy);

private:
	int m_handle;
	int m_graphWidth;
	int m_graphHeight;

	int m_walkSe;

	float m_posX;
	float m_posY;

	bool m_isTurn;	// �`�����
};