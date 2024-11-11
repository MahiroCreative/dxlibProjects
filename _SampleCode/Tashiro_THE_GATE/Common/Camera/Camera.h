#pragma once
#include "Collidable.h"
#include "Geometry/Vec3.h"

// MEMO: 当たり判定ありにするなら先頭の_を外す
#define _USE_CAMERA_COLLIDABLE

struct CameraInfo
{
	// Tpsフラグ
	bool isTps = true;
	// near, far
	float n = 1.0f;
	float f = 100.0f;
	// 視野角
	float fov = 0.0f;
	// ターゲット位置
	Vec3 targetPos;
	// 正面方向
	Vec3 front;
	// 右方向
	Vec3 right;
#ifndef USE_CAMERA_COLLIDABLE
	// 場所
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
	/// 情報の取得
	/// </summary>
	/// <returns>情報群</returns>
	const CameraInfo& GetInfo() const { return m_info; }
	/// <summary>
	/// 初期縦方向の回転
	/// </summary>
	/// <returns>rot</returns>
	static const Quaternion& GetStartVerticalRot();

	/// <summary>
	/// near,farを設定
	/// </summary>
	/// <param name="n">near</param>
	/// <param name="f">far</param>
	void SetNearFar(float n, float f);
	/// <summary>
	/// 視野角の設定
	/// </summary>
	/// <param name="angle">角度</param>
	void SetFov(float angle);
	/// <summary>
	/// 初期位置の設定
	/// </summary>
	/// <param name="targetPos">カメラの注視点</param>
	void SetTargetPos(const Vec3& targetPos);

	/// <summary>
	/// カメラの有効化
	/// </summary>
	void AppInfo();

	/// <summary>
	/// カメラの場所を取得
	/// </summary>
	/// <returns>pos</returns>
	const Vec3& GetPos() const;

protected:
	/// <summary>
	/// カメラの向きを回転
	/// </summary>
	/// <param name="angle">角度</param>
	/// <param name="axis">軸</param>
	void Rotation(float angle, const Vec3& axis = Vec3::Up());

	/// <summary>
	/// カメラの距離を取得
	/// </summary>
	/// <returns></returns>
	float GetDistance() const;

protected:
#ifdef USE_CAMERA_COLLIDABLE
	std::shared_ptr<GateManager> m_gateMgr;
	MyEngine::ColliderSphere* m_collider;
#endif
	// 情報
	CameraInfo m_info;
};

