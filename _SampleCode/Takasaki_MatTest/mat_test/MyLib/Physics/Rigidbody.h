#pragma once
#include "../Vec3.h"

struct Transform//�}���I�M�����N�V�[�ł͂�����g�p����
{
	Vec3 Translate;
	Vec3 Rotate;
	Vec3 Scale;//�����蔻��Ƃ͕ʂ̃X�P�[��
};

namespace MyEngine
{
	class Rigidbody final
	{
	public:
		Rigidbody();
		~Rigidbody();

		void Init(const Vec3& pos = Vec3());

		/* Getter/Setter */
		const Vec3& GetPos() const { return m_pos; }
		const Vec3& GetNextPos() const { return m_nextPos; }
		const Vec3& GetVelocity() const { return m_velocity; }
		const Vec3& GetPrevVelocity()const { return m_prevVelocity; }
		const Vec3& GetDir() const { return m_dir; }

		void ChangePosition(Vec3 pos);
		void SetPos(Vec3 pos);
		void SetNextPos(const Vec3& nextPos) { m_nextPos = nextPos; }
		void SetVelocity(const Vec3& velocity);
		void SetPrevVelocity(const Vec3& velocity) { m_prevVelocity = velocity; }
		void AddVelocity(const Vec3& velocity) { m_velocity += velocity; };
		//void SetGravity(const float& gravity) { m_gravityPower = gravity; }

	private:
		Vec3 m_pos;
		Vec3 m_nextPos;
		Vec3 m_velocity;
		Vec3 m_prevVelocity;
		Vec3 m_dir;
		//float m_gravityPower;//���L����
		
	};
}

