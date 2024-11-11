#include "GateBullet.h"
#include "GateManager.h"
#include "Collider/ColliderSphere.h"
#include "Collider/ColliderBox.h"

namespace
{
	// FIXME: 後々外部化予定
	constexpr float RADIUS = 1.0f;
	constexpr float SPEED = 1.0f;
}

GateBullet::GateBullet(const std::shared_ptr<GateManager>& gateMgr, GateKind kind) :
	Collidable(Priority::LOW, ObjectTag::GATE_BULLET),
	m_gateMgr(gateMgr),
	m_kind(kind),
	m_isBreak(false)
{
}

GateBullet::~GateBullet()
{
}

void GateBullet::Init(const Vec3& pos, const Vec3& dir)
{
	OnEntryPhysics();
	m_rigid.SetGravity(false);
	m_rigid.SetPos(pos);
	m_rigid.SetVelocity(dir.GetNormalized() * SPEED);
	auto colider = std::dynamic_pointer_cast<MyEngine::ColliderSphere>(CreateCollider(MyEngine::ColKind::SPHERE));
	colider->radius = RADIUS;
	colider->isTrigger = false;

	m_throughTag.push_back(ObjectTag::CAMERA);
	m_throughTag.push_back(ObjectTag::PALYER);
}

void GateBullet::OnCollideEnter(MyEngine::Collidable* collider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	Collidable::OnCollideEnter(collider, colIndex, hitInfo);

	auto tag = collider->GetTag();
	if (tag == ObjectTag::SYSTEM_WALL)
	{
		m_gateMgr->CreateGate(m_kind, collider, hitInfo, Vec3::Up());
	}
	else if (tag == ObjectTag::FLOOR)
	{
		auto velDir = m_rigid.GetDir();
		velDir.y = 0;
		m_gateMgr->CreateGate(m_kind, collider, hitInfo, velDir.GetNormalized());
	}

	m_isBreak = true;
}
