#include "Collidable.h"
#include <cassert>
#include "Vec3.h"
#include "DebugDraw.h"
#include "Physics.h"
#include "Collider/Colliders.h"

using namespace MyEngine;

Collidable::Collidable(Priority priority, ObjectTag tag) :
	m_priority(priority),
	m_tag(tag),
	m_isEntry(false)
{
}

Collidable::~Collidable()
{
}

void Collidable::End()
{
	if (m_isEntry)
	{
		auto& physics = Physics::GetInstance();
		physics.Exit(shared_from_this());
		m_isEntry = false;
	}
}

ColliderBase* Collidable::GetColliderData(int index) const
{
	return m_collider.at(index).get();
}

void Collidable::OnCollideEnter(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Collide", "当たった", colider);
#endif
}

void Collidable::OnCollideStay(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Collide", "当たっている", colider);
#endif
	if (colider->GetTag() == ObjectTag::FLOOR)
	{
		auto vel = m_rigid.GetVelocity();
		vel.y = 0;
		m_rigid.SetVelocity(vel);
	}
}

void Collidable::OnCollideExit(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Collide", "離れた", colider);
#endif
}

void Collidable::OnTriggerEnter(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Trigger", "当たった", colider);
#endif
}

void Collidable::OnTriggerStay(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Trigger", "当たっている", colider);
#endif
}

void Collidable::OnTriggerExit(Collidable* colider, int colIndex, const CollideHitInfo& hitInfo)
{
#ifdef _DEBUG
	SendCollideInfo("Trigger", "離れた", colider);
#endif
}

const Vec3& Collidable::GetPos() const
{
	return m_rigid.GetPos();
}

const Vec3& MyEngine::Collidable::GetVelocity() const
{
	return m_rigid.GetVelocity();
}

void Collidable::AddForce(const Vec3& dir, float power)
{
	m_rigid.AddForce(dir, power);
}

/// <summary>
/// Physicsに追加する
/// </summary>
void Collidable::OnEntryPhysics()
{
	if (m_isEntry) return;
	auto& physics = MyEngine::Physics::GetInstance();
	physics.Entry(shared_from_this());
	m_isEntry = true;
}

/// <summary>
/// Physicsから削除する
/// </summary>
void Collidable::OnExistPhysics()
{
	if (!m_isEntry) return;
	auto& physics = MyEngine::Physics::GetInstance();
	physics.Exit(shared_from_this());
	m_isEntry = false;
}

std::shared_ptr<ColliderBase> Collidable::CreateCollider(const ColKind& kind)
{
	std::shared_ptr<ColliderBase> col;
	if (kind == ColKind::SPHERE)
	{
		col = std::make_shared<ColliderSphere>();
	}
	else if (kind == ColKind::CAPSULE)
	{
		col = std::make_shared<ColliderCapsule>();
	}
	else if (kind == ColKind::TERRAIN)
	{
		col = std::make_shared<ColliderTerrain>();
	}
	else if (kind == ColKind::BOX)
	{
		col = std::make_shared<ColliderBox>();
	}

	if (!col)
	{
		assert(false);
		col = std::make_shared<ColliderSphere>();
	}

	m_collider.emplace_back(col);

	return col;
}

#ifdef _DEBUG
#include "ObjectTag.h"
#include <unordered_map>
void Collidable::SendCollideInfo(const char* start, const char* const end, Collidable* collider)
{
	const std::unordered_map<ObjectTag, const char* const> TAG_NAME =
	{
		{ ObjectTag::PALYER, "プレイヤー" },
		{ ObjectTag::CAMERA, "カメラ" },
		{ ObjectTag::FLOOR, "床" },
		{ ObjectTag::FLOOR_SMALL, "小さい床" },
		{ ObjectTag::FLOOR_MOVE, "動く床" },
		{ ObjectTag::ROOF,	 "天井" },
		{ ObjectTag::SYSTEM_WALL, "システム壁" },
		{ ObjectTag::NO_GATE_WALL, "ゲート生成不可壁" },
		{ ObjectTag::DUMMY_WALL, "ダミー壁" },
		{ ObjectTag::GATE, "ゲート" },
		{ ObjectTag::GATE_BULLET, "ゲートの弾" },
		{ ObjectTag::HAND_OBJ, "手で持てるオブジェ" },
		{ ObjectTag::BUTTON, "ボタン" },
		{ ObjectTag::PISTON, "ピストン" },
		{ ObjectTag::TURRET, "タレット" },
		{ ObjectTag::TURRET_BULLET, "タレットの球" },
		{ ObjectTag::LASER_LAUNCH_PAD, "レーザーの開始地点" },
		{ ObjectTag::LASER_CATCHER, "レーザーの終了地点" },
		{ ObjectTag::LASER_BULLET, "レーザーの弾" },
		{ ObjectTag::GIMMICK, "ギミック" },
		{ ObjectTag::ELEVATOR, "エレベータ" },
		{ ObjectTag::CHECK_POINT, "チェックポイント" },
		{ ObjectTag::NONE, "何かしら" },
	};

	printf("%s:%sが%sと%s\n", start, TAG_NAME.at(m_tag), TAG_NAME.at(collider->GetTag()), end);
}
#endif