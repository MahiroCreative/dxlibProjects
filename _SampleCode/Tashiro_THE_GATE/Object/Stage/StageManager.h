#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Vec3.h"
#include "Quaternion.h"

class GateManager;
class Object3DBase;
class CheckPoint;
class Player;
namespace MyEngine
{
	class ColliderBase;
	enum class ColKind;
}

class StageManager
{
private:
	struct ModelData
	{
		Vec3 pos;
		Vec3 scale;
		Quaternion rot;
	};
public:
	StageManager(const wchar_t* const stageName);
	~StageManager();

	void Init(Player* player, GateManager* gateMgr);
	void Update();
	void Draw() const;
	void End();

	void Restart();

	void UpdateCheckPoint(int checkNo);
	const Vec3& GetCheckPoint() const;

private:
	void LoadAndCreateObject(int stageNo, Player* player, GateManager* gateMgr);
	void LoadGimmickLinkInfo(int stageNo);
	void LoadFloorMoveInfo(int stageNo);
	void LoadCheckPoint(int stageNo);

	MyEngine::ColliderBase* LoadBoxColInfo(int handle, const ModelData& data);
	MyEngine::ColliderBase* LoadSphereColInfo(int handle, const ModelData& data);

private:
	using CreateColliderFunc_t = MyEngine::ColliderBase*(StageManager::*)(int, const ModelData&);
	std::unordered_map<MyEngine::ColKind, CreateColliderFunc_t> m_createFunc;
	std::vector<std::shared_ptr<Object3DBase>> m_objs;
	std::vector<std::shared_ptr<CheckPoint>> m_checkPoints;

	const wchar_t* const m_stageName;
};

