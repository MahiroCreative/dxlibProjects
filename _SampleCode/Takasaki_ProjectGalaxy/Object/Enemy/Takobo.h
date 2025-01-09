#pragma once
#include "Enemy.h"
#include"EnemySphere.h"



/// <summary>
/// ���E�Ɉړ����A���Ԋu�Ŏˌ����Ă���Ge
/// ���݂�����ƂԂ��
/// </summary>
class Takobo : public Enemy
{
public:

	/// <param name="m_modelhandle">�G�l�~�[�̃��f��</param>
	/// <param name="obj">�e����^����I�u�W�F</param>
	Takobo(Vec3 pos);
	virtual ~Takobo();

	void Init();
	void Update();
	void SetMatrix();
	void DeleteManage();
	void Draw();

	virtual void OnCollideEnter(std::shared_ptr<Collidable> colider,MyEngine::ColliderBase::ColideTag ownTag,MyEngine::ColliderBase::ColideTag targetTag);

	Vec3 GetMyPos();
	int WatchHp() const { return m_Hp; }
	float GetColRadius() { return m_radius; }

	float GetIdleSpeed() { return m_idleSpeed; }

	void SetTarget(std::shared_ptr<Collidable> target);
	void SetNormVec(Vec3 norm) { m_normVec = norm; }

	std::list<std::shared_ptr<EnemySphere>> GetAttackObj() { return m_sphere; }
	

	//�����o�֐��|�C���^
	using enemyState_t = void(Takobo::*)();
	enemyState_t m_enemyUpdate;
private:
	/// <summary>
	/// �ʏ�(�N�[���_�E��)���
	/// </summary>
	void IdleUpdate();
	/// <summary>
	/// ���̂𐶐����čU��
	/// </summary>
	void AttackSphereUpdate();

	Vec3 GetAttackDir() const;
private:
	int m_Hp;

	int m_attackCoolDownCount;

	float m_radius = 0;

	int m_modelHandle = 0;

	int m_createFrameCount = 0;

	float m_centerToEnemyAngle;

	float m_idleSpeed = 0;

	int m_sphereNum = 0;
	int m_bombNum = 0;
	int m_shotSEHandle;

	Vec3 m_vec;
	Vec3 m_attackDir;
	Vec3 m_moveShaftPos;
	Vec3 m_normVec;
	Vec3 m_nowPlanetPos;
	std::shared_ptr<Collidable> m_target;
	//�A�j���[�V�����ϐ�
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_anim_attack = 0;

	std::list<std::shared_ptr<EnemySphere>> m_sphere;
};

