#pragma once
#include "SceneBase.h"
#include <vector>
#include <list>
#include <memory>

struct Vec3;
class GateManager;
class StageManager;
class CameraManager;
class Player;
enum class CameraKind;

class SceneMain final : public SceneBase
{
public:
	SceneMain(const wchar_t* const stageName);
	~SceneMain() {}

	// シーンに入るときの初期化処理
	void Init() override;
	// 毎フレーム行う更新処理
	void Update(bool isFade) override;
	// 毎フレーム行う描画処理
	void Draw() const override;
	// シーンを抜けるときの処理
	void End() override;

private:
	void MainUpdate();
	void GameOverUpdate();

	void DrawNormal() const;
	void DrawBlend() const;
	void DrawCommonUI() const;
	void DrawExistUI() const;
	void DrawDeathUI() const;

	void DrawGateBlend(int rt, CameraKind gate, CameraKind from) const;
	void DrawModelBlend(int rt, int tex1, int tex2, CameraKind camera) const;

private:
	using UpdateFunc_t = void(SceneMain::*)();
	UpdateFunc_t m_updateFunc;

	std::shared_ptr<GateManager> m_gateMgr;
	std::shared_ptr<StageManager> m_stageMgr;
	std::shared_ptr<CameraManager> m_cameraMgr;

	std::shared_ptr<Player> m_player;

	std::vector<int> m_rtTable;

	const wchar_t* const m_stageName;

	int m_depthRT;
	int m_depthRT2;
	int m_time;
	int m_current;
};
