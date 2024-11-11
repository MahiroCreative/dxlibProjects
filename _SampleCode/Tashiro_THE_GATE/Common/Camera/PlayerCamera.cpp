#include "PlayerCamera.h"
#include "Input.h"
#include "CommandList.h"
#include "Game.h"
#include "MathHelp.h"
#include "Object/Gate/Gate.h"
#include "Collider/ColliderCapsule.h"

PlayerCamera::PlayerCamera()
{
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(const Vec3& playerPos)
{
	constexpr float ANGLE_CAMERA = 1.0f;
	// カメラの回転
	auto& input = Input::GetInstance();
	const auto& trigger = input.GetTriggerData();
	m_info.targetPos = playerPos;
	if (trigger.RStick.SqLength() > 0.0f)
	{
		// 左右回転
		Rotation(trigger.RStick.x * ANGLE_CAMERA);
		// 上下回転
		if (trigger.RStick.y)
		{
			const auto& axis = Vec3::Cross(m_info.front, Vec3::Up());
			Rotation(trigger.RStick.y * ANGLE_CAMERA, axis);
		}
		// MEMO: もし自由に動かしたい場合はこちらに変更
		// m_camera->Rotation(trigger.RStick.y, info.right);
	}
	if (input.IsTriggerd(Command::BTN_CHANGE_VIEW))
	{
		m_info.isTps = !m_info.isTps;
	}
}

void PlayerCamera::OnWarp(const Vec3& preVelDir, const Vec3& newVelDir, const Vec3& pos)
{
	auto rad = Quaternion::GetQuaternion(preVelDir, newVelDir).GetRadian();
	auto rot = Quaternion::AngleAxis(rad.y * Game::RAD_2_DEG, Vec3::Up());
	m_info.front = rot * m_info.front;
	m_info.right = rot * m_info.right;
	m_info.targetPos = pos;

	auto newPos = m_info.targetPos - m_info.front * GetDistance();
#ifdef USE_CAMERA_COLLIDABLE
	m_rigid.SetPos(newPos);
	m_collider->isTrigger = true;
#else
	m_info.cameraPos = newPos;
#endif
}
