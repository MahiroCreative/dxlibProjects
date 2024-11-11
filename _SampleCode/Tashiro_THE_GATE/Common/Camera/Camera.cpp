#include "Camera.h"
#include <DxLib.h>
#include "Game.h"
#include "Easing.h"
#include "Collider/ColliderSphere.h"
#include "Object/Gate/Gate.h"
#include "Object/Gate/GateManager.h"

namespace
{
	constexpr float DEF_NEAR = 1.0f;
	constexpr float DEF_FAR = 100.0f;

	constexpr float DEF_FOV_ANGLE = 60.0f * Game::DEG_2_RAD;

	constexpr float CAMERA_DISTANCE = 10.0f;
	const Vec3 DIR_RIGHT_BASE = Vec3(-1, 0, 0);
	const Quaternion START_VERTICAL_ROTATION = Quaternion::AngleAxis(30.0f, DIR_RIGHT_BASE);
	const Vec3 DIR_FRONT_BASE = (START_VERTICAL_ROTATION * Vec3(0, 0, -1)).GetNormalized();
}

Camera::Camera()
#ifdef USE_CAMERA_COLLIDABLE
	: 
	Collidable(Priority::LOW, ObjectTag::CAMERA),
	m_gateMgr(nullptr),
	m_collider(nullptr)
#endif
{
	m_info.n = DEF_NEAR;
	m_info.f = DEF_FAR;
	m_info.fov = DEF_FOV_ANGLE;
	m_info.front = DIR_FRONT_BASE;
	m_info.right = DIR_RIGHT_BASE;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	// 位置を更新
#ifdef USE_CAMERA_COLLIDABLE
	auto nowPos = m_rigid.GetPos();
#else
	auto& nowPos = m_info.cameraPos;
#endif
	auto newPos = m_info.targetPos - m_info.front * CAMERA_DISTANCE;

#ifdef USE_CAMERA_COLLIDABLE
	auto nextPos = Lerp(nowPos, newPos, 0.1f);
	m_rigid.SetVelocity(nextPos - nowPos);
#else
	nowPos = Easing::Lerp(nowPos, newPos, 0.1f);
#endif
}

#ifdef USE_CAMERA_COLLIDABLE
void Camera::OnTriggerEnter(MyEngine::Collidable* colider, const Vec3& hitPos)
{
	MyEngine::Collidable::OnTriggerExit(colider, hitPos);
	
	auto tag = colider->GetTag();
	if (tag == ObjectTag::GATE)
	{
		// 二つのゲートが作られていなければ無視
		if (!m_gateMgr->IsCreateBothGates()) return;
		// スルータグに対象のゲートが作られているものを無視するようにする
		auto gate = dynamic_cast<Gate*>(colider);
		m_throughTag.emplace_back(gate->GetHitObjectTag());
	}
}

void Camera::OnTriggerExit(MyEngine::Collidable* colider, const Vec3& hitPos)
{
	MyEngine::Collidable::OnTriggerExit(colider, hitPos);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::GATE)
	{
		if (!m_gateMgr->IsCreateBothGates()) return;
		// 追加したスルータグを消す
		m_throughTag.pop_back();
	}
	else if (tag == ObjectTag::SYSTEM_WALL || tag == ObjectTag::FLOOR)
	{
		m_collider->isTrigger = false;
	}
}

void Camera::OnEntity()
{
	Collidable::OnEntryPhysics();
	m_rigid.SetGravity(false);
	m_throughTag.emplace_back(ObjectTag::PALYER);
	m_throughTag.emplace_back(ObjectTag::GATE);
	m_throughTag.emplace_back(ObjectTag::GATE_BULLET);
	m_collider = dynamic_cast<MyEngine::ColliderSphere*>(CreateCollider(MyEngine::ColliderBase::Kind::SPHERE).get());
	m_collider->radius = 5.0f;
}
#endif

const Quaternion& Camera::GetStartVerticalRot()
{
	return START_VERTICAL_ROTATION;
}

/// <summary>
/// NearFarの設定
/// </summary>
/// <param name="n">Near</param>
/// <param name="f">Far</param>
void Camera::SetNearFar(float n, float f)
{
	m_info.n = n;
	m_info.f = f;
}

/// <summary>
/// 画角の設定
/// </summary>
/// <param name="angle">角度(deg)</param>
void Camera::SetFov(float angle)
{
	m_info.fov = angle * Game::DEG_2_RAD;
}

/// <summary>
/// 初期位置
/// </summary>
/// <param name="targetPos">ターゲットの座標</param>
void Camera::SetTargetPos(const Vec3& targetPos)
{
	m_info.targetPos = targetPos;
	auto cameraPos = targetPos - m_info.front * CAMERA_DISTANCE;
#ifdef USE_CAMERA_COLLIDABLE
	m_rigid.SetPos(cameraPos);
#else
	m_info.cameraPos = cameraPos;
#endif
}

void Camera::Rotation(float angle, const Vec3& axis)
{
	// 回転度0なら早期リターン
	if (!angle) return;

	const auto& rot = Quaternion::AngleAxis(angle, axis);
	m_info.front = rot * m_info.front;
	m_info.right = rot * m_info.right;
}

void Camera::AppInfo()
{
	SetCameraNearFar(m_info.n, m_info.f);
	SetupCamera_Perspective(m_info.fov);
#ifdef USE_CAMERA_COLLIDABLE
	SetCameraPositionAndTarget_UpVecY(m_rigid.GetPos().VGet(), m_info.targetPos.VGet());
#else
	if (m_info.isTps)
	{
		SetCameraPositionAndTarget_UpVecY(m_info.cameraPos.VGet(), m_info.targetPos.VGet());
	}
	else
	{
		SetCameraPositionAndTarget_UpVecY(m_info.targetPos.VGet(), (m_info.targetPos + m_info.front).VGet());
	}
#endif
}

const Vec3& Camera::GetPos() const
{
	if (m_info.isTps)
	{
		return m_info.cameraPos;
	}
	else
	{
		return m_info.targetPos;
	}
}

float Camera::GetDistance() const
{
	return CAMERA_DISTANCE;
}
