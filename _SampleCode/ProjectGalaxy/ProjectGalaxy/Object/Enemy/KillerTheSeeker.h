#pragma once
#include "Enemy.h"

class Killer;

class KillerTheSeeker :
    public Enemy
{
public:
    KillerTheSeeker(Vec3 pos);
    virtual ~KillerTheSeeker();

    void Init();
    void Update();
	void DeleteManage();
    void Draw();

	virtual void OnCollideEnter(std::shared_ptr<Collidable> colider,MyEngine::ColliderBase::ColideTag tag);

	Vec3 GetMyPos();
	int WatchHp() const { return m_Hp; }
	float GetColRadius() { return m_radius; }

	float GetIdleSpeed() { return m_idleSpeed; }

	void SetTarget(std::shared_ptr<Collidable> target);
	void SetNormVec(Vec3 norm) { m_normVec = norm; }
	void SetVelocity(Vec3 vel) { m_velocity = vel; }
	Vec3 GetVelocity() const { return m_velocity; }
	std::list<std::shared_ptr<Killer>> GetAttackObj() { return m_sphere; }

	//�����o�֐��|�C���^
	using enemyState_t = void(KillerTheSeeker::*)();
	enemyState_t m_enemyUpdate;


	int m_Hp;
private:
	/// <summary>
	/// �ʏ�(�N�[���_�E��)���
	/// </summary>
	void IdleUpdate();
	/// <summary>
	/// ���̂𐶐����čU��
	/// </summary>
	void AttackSphereUpdate();
	void AttackRollingUpdate();

	Vec3 GetAttackDir() const;
private:
	
	int m_color;
	int m_attackCount;

	int m_attackCoolDownCount;

	float m_radius = 0;

	int m_modelHandle = 0;

	int m_createFrameCount = 0;

	float m_centerToEnemyAngle;

	float m_idleSpeed = 0;

	int m_sphereNum = 0;
	int m_bombNum = 0;
	int m_shotSEHandle;
	int m_counterHitSEHandle;

	bool m_isSecondFase;
	bool m_isHitFrame;
	int m_hitFrame;

	Vec3 m_vec;
	Vec3 m_attackDir;
	Vec3 m_velocity;
	Vec3 m_moveShaftPos;
	Vec3 m_normVec;
	Vec3 m_nowPlanetPos;
	std::shared_ptr<Collidable> m_target;
	//�A�j���[�V�����ϐ�
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_anim_attack = 0;

	std::list<std::shared_ptr<Killer>> m_sphere;
};

