#pragma once
#include <array>
#include <memory>

class Camera;
class GateManager;
enum class CameraKind
{
	PLAYER,
	GATE_A,
	GATE_B,
	GATE_A_FROM_B,
	GATE_B_FROM_A,
	MAX
};

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// �J�����̗L����
	/// </summary>
	/// <param name="kind">���</param>
	void AppInfo(CameraKind kind);
	/// <summary>
	/// �J�����ɓ����蔻�������@USE_CAMERA_COLLIDABLE���Ȃ��ƗL���ł͂Ȃ�
	/// </summary>
	/// <param name="kind">���</param>
	/// <param name="gateMgr">�Q�[�g�}�l�[�W���[</param>
	void OnEntity(CameraKind kind, const std::shared_ptr<GateManager>& gateMgr);

	/// <summary>
	/// �J�����̎擾
	/// </summary>
	/// <param name="kind">���</param>
	/// <returns>�J����</returns>
	std::shared_ptr<Camera> GetCamera(CameraKind kind) const { return m_cameras[static_cast<size_t>(kind)]; }

private:
	std::array<std::shared_ptr<Camera>, static_cast<size_t>(CameraKind::MAX)> m_cameras;
};

