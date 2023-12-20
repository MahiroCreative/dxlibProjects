#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"


class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw() const;
	void End();		// �V�[���̏I������

	// �V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

private:
	// ��ʓ��ɓ����ɑ��݂ł���G�̍ő吔
	static constexpr int kEnemyMax = 16;

private:
	int m_playerHandle;	// �v���C���[�̃O���t�B�b�N
	int m_enemyHandle;	// �G�̃O���t�B�b�N
	int m_bgHandle;		// �w�i�̃O���t�B�b�N

	int m_bgmHandle;	// BGM

	int m_enemyStartSe;	// �G�̗�����SE
	int m_hitSe;		// ����������SE
	int m_walkSe;		// ��������SE

	// ���̃N���X���Ă΂ꂽ���_�Ń����o�ϐ��̃N���X�̓R���X�g���N�^���Ă΂�邽��
	// ���̃N���X�̃R���X�g���N�^�ŏ��������Ȃ��Ă��悢
	// ���������Ă����ق����ǂ�����
	// m_player() �ƈ����Ȃ��ŃR���X�g���N�^�ɏ����Ă���
	Player m_player;
	Enemy m_enemy[kEnemyMax];

	bool m_isGameOver;		// �Q�[���I�[�o�[���ǂ����̃t���O
	bool m_isSceneEnd;		// �V�[�����I�����鎞��true�ɂ���
	int m_playFrameCount;	// �����c���Ă��鎞��

	// �J���̐�������
	int m_enemyCreateNum;	// ���܂łɐ��Y�����G�̐�
	int m_enemyWaitFrame;	// �G�����܂ł̑҂�����

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};