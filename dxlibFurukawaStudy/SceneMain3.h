#pragma once
// ���܂�w�b�_�[�t�@�C���Ńw�b�_�[�t�@�C����
// �C���N���[�h����͖̂]�܂����Ȃ�
//#include "Player.h"

// �N���X�̃v���g�^�C�v�錾
class Player;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw() const;	// �֐���const�����邱�Ƃł��̊֐��̓�����
	// �����o�[�ϐ���ύX�ł��Ȃ��Ȃ�

private:
	// ��������\������p�̒萔
	// static constexpr int kPlayerNum = 65536 * 8;

private:

	int m_frameCount;

	Player* m_pPlayer;
};