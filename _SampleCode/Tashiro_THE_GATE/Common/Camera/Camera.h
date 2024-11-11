#pragma once
#include "Collidable.h"
#include "Geometry/Vec3.h"

// MEMO: �����蔻�肠��ɂ���Ȃ�擪��_���O��
#define _USE_CAMERA_COLLIDABLE

struct CameraInfo
{
	// Tps�t���O
	bool isTps = true;
	// near, far
	float n = 1.0f;
	float f = 100.0f;
	// ����p
	float fov = 0.0f;
	// �^�[�Q�b�g�ʒu
	Vec3 targetPos;
	// ���ʕ���
	Vec3 front;
	// �E����
	Vec3 right;
#ifndef USE_CAMERA_COLLIDABLE
	// �ꏊ
	Vec3 cameraPos;
#endif
};

namespace MyEngine
{
	class ColliderSphere;
}
struct Quaternion;
class GateManager;

#ifdef USE_CAMERA_COLLIDABLE
class Camera final : public MyEngine::Collidable
#else
class Camera
#endif
{
public:
	Camera();
	virtual ~Camera();

	void Update();
#ifdef USE_CAMERA_COLLIDABLE
	virtual void OnTriggerEnter(MyEngine::Collidable* colider, const Vec3& hitPos) override;
	virtual void OnTriggerExit(MyEngine::Collidable* colider, const Vec3& hitPos) override;
	void OnEntity();
	void SetGateManager(const std::shared_ptr<GateManager>& gateMgr) { m_gateMgr = gateMgr; }
#endif
	/// <summary>
	/// ���̎擾
	/// </summary>
	/// <returns>���Q</returns>
	const CameraInfo& GetInfo() const { return m_info; }
	/// <summary>
	/// �����c�����̉�]
	/// </summary>
	/// <returns>rot</returns>
	static const Quaternion& GetStartVerticalRot();

	/// <summary>
	/// near,far��ݒ�
	/// </summary>
	/// <param name="n">near</param>
	/// <param name="f">far</param>
	void SetNearFar(float n, float f);
	/// <summary>
	/// ����p�̐ݒ�
	/// </summary>
	/// <param name="angle">�p�x</param>
	void SetFov(float angle);
	/// <summary>
	/// �����ʒu�̐ݒ�
	/// </summary>
	/// <param name="targetPos">�J�����̒����_</param>
	void SetTargetPos(const Vec3& targetPos);

	/// <summary>
	/// �J�����̗L����
	/// </summary>
	void AppInfo();

	/// <summary>
	/// �J�����̏ꏊ���擾
	/// </summary>
	/// <returns>pos</returns>
	const Vec3& GetPos() const;

protected:
	/// <summary>
	/// �J�����̌�������]
	/// </summary>
	/// <param name="angle">�p�x</param>
	/// <param name="axis">��</param>
	void Rotation(float angle, const Vec3& axis = Vec3::Up());

	/// <summary>
	/// �J�����̋������擾
	/// </summary>
	/// <returns></returns>
	float GetDistance() const;

protected:
#ifdef USE_CAMERA_COLLIDABLE
	std::shared_ptr<GateManager> m_gateMgr;
	MyEngine::ColliderSphere* m_collider;
#endif
	// ���
	CameraInfo m_info;
};

