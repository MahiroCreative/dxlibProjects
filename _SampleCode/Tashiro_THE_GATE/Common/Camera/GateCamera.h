#pragma once
#include "Camera.h"

class Gate;

class GateCamera : public Camera
{
public:
	GateCamera();
	virtual ~GateCamera();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="dir">����</param>
	/// <param name="playerCameraFront">�v���C���[�J�����̐��ʕ���</param>
	void Update(const Vec3& dir, const Vec3& playerCameraFront);

	void SetBaseViewDir(const Vec3& dir) { m_baseViewDir = dir; }

private:
	Vec3 m_baseViewDir;
};

