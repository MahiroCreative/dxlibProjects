#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Object/Object3DBase.h"

class FileBase;
class Camera;
class PlayerCamera;
class GateManager;
class HandObject;
class AnimController;
namespace MyEngine
{
	class ColliderSphere;
	class ColliderCapsule;
	struct CollideHitInfo;
}

class Player : public Object3DBase
{
private:
	enum class State
	{
		IDLE,
		MOVE,
		JUMP,
		AERIAL,
		LANDING,
		DEATH,
	};

public:
	Player(const std::shared_ptr<PlayerCamera>& camera, const std::shared_ptr<GateManager>& gateMgr);
	virtual ~Player();

	void Init(bool isOneHand);
	void Restart(const Vec3& pos);
	void Update() override;
	void Draw() const override;
	void DrawHpUI() const;

	void OnDamage(int damage);

	bool IsDeath() const { return m_isDeath; }
	std::shared_ptr<Camera> GetCamera() const;

	virtual void OnCollideEnter(Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo) override;
	virtual void OnCollideStay(Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo) override;
	virtual void OnTriggerStay(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo) override;
	virtual void OnTriggerExit(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo) override;

private:
	void HandUpdate();
	void RecoverHpUpdate();
	void HpBarUpdate();
	void ThroughTagUpdate();
	void AnimUpdate();

	void IdleUpdate();
	void WalkUpdate();
	void JumpUpdate();
	void AerialUpdate();
	void LandingUpdate();
	void DeathUpdate();

	void OnIdle();
	void OnWalk();
	void OnJump();
	void OnAerial();
	void OnLanding();
	void OnDeath();

	void OnShot();
	void OnHand(MyEngine::Collidable* obj);

private:
	using UpdateFunc_t = void(Player::*)();
	UpdateFunc_t m_updateFunc;

	std::unordered_map<std::wstring, std::shared_ptr<FileBase>> m_files;

	std::shared_ptr<PlayerCamera> m_camera;
	std::shared_ptr<GateManager> m_gateMgr;
	std::shared_ptr<AnimController> m_anim;

	std::shared_ptr<MyEngine::ColliderSphere> m_centerCol;
	std::shared_ptr<MyEngine::ColliderSphere> m_handCol;

	State m_nowState;

	HandObject* m_handObj;

	Quaternion m_nextRot;

	int m_hp;
	int m_preHp;
	int m_receverFrame;
	int m_shotInteval;
	int m_shakeHpBarFrame;

	bool m_isOneHand;
	bool m_isDeath;
	bool m_isRecever;
	bool m_isGround;
	bool m_isAddThroughTag;
	bool m_isCatch;
	bool m_isWarp;
};
