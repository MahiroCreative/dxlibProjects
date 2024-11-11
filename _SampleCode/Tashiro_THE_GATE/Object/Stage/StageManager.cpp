#include "StageManager.h"
#include <list>
#include "Utility.h"
#include "StageDataManager.h"
#include "SaveDataManager.h"
#include "CheckPoint.h"
#include "Collider/Colliders.h"
#include "Object/HandObject.h"
#include "Object/Gimmick/Door.h"
#include "Object/Gimmick/Button.h"
#include "Object/Gimmick/Piston.h"
#include "Object/Gimmick/Turret/Turret.h"
#include "Object/Gimmick/Laser/LaserCatcher.h"
#include "Object/Gimmick/Laser/LaserLaunchPad.h"
#include "Object/Gimmick/MoveFloor/MoveFloorManager.h"

namespace
{
	const wchar_t* const BASE_PATH = L"Data/Stage/";
	const wchar_t* const MODEL_INFO_PATH = L"StageModelInfo";
	const wchar_t* const GIMMICK_INFO_PATH = L"StageGimmickInfo";
	const wchar_t* const FLOOR_MOVE_INFO_PATH = L"FloorMoveInfo";
	const wchar_t* const CHECK_POINT_INFO_PATH = L"CheckPointInfo";
	const wchar_t* const EXTENSION = L".loc";

	const wchar_t* const FILE_WALL = L"M_Wall";
	const wchar_t* const FILE_DUMMY_WALL = L"M_DummyWall";
	const wchar_t* const FILE_FLOOR = L"M_Floor";
	const wchar_t* const FILE_DOOR = L"M_Door";
	const wchar_t* const FILE_DOOR_ARCH = L"M_DoorArch";
	const wchar_t* const FILE_HAND_OBJ = L"M_HandObj";
	const wchar_t* const FILE_BUTTON = L"M_Button";
	const wchar_t* const FILE_TURRET = L"M_Turret";
//	const wchar_t* const FILE_LASER_LUNCH_PAD = L"M_Turret";
//	const wchar_t* const FILE_LASER_CATHCER = L"M_Turret";
	const wchar_t* const FILE_PISTON = L"M_Piston";

	const std::unordered_map<std::string, ObjectTag> OBJECT_TAG =
	{
		{ "SystemWall", ObjectTag::SYSTEM_WALL },
		{ "SystemWallArc", ObjectTag::SYSTEM_WALL },
		{ "NoGateWall", ObjectTag::NO_GATE_WALL },
		{ "DummyWall", ObjectTag::DUMMY_WALL },
		{ "Floor", ObjectTag::FLOOR },
		{ "FloorSmall", ObjectTag::FLOOR },
		{ "RoofDoor", ObjectTag::ROOF },
		{ "DoorArch", ObjectTag::NONE },
	};
	const std::unordered_map<std::string, const wchar_t* const> MODEL_ID =
	{
		{ "SystemWall", FILE_WALL },
		{ "NoGateWall", FILE_WALL },
		{ "DummyWall", FILE_DUMMY_WALL },
		{ "Floor", FILE_FLOOR },
		{ "Door", FILE_DOOR },
		{ "DoorArch", FILE_DOOR_ARCH },
		{ "HandObj", FILE_HAND_OBJ },
		{ "Button", FILE_BUTTON },
		{ "Turret", FILE_TURRET },
		{ "LaserLaunchPad", FILE_HAND_OBJ },
		{ "LaserCatcher", FILE_HAND_OBJ },
		{ "Piston", FILE_PISTON },
	};
}

StageManager::StageManager(const wchar_t* const stageName) :
	m_stageName(stageName)
{
	m_createFunc[MyEngine::ColKind::BOX] = &StageManager::LoadBoxColInfo;
	m_createFunc[MyEngine::ColKind::SPHERE] = &StageManager::LoadSphereColInfo;
}

StageManager::~StageManager()
{
}

void StageManager::Init(Player* player, GateManager* gateMgr)
{
	auto& stageDataMgr = StageDataManager::GetInstance();
	auto stageNo = stageDataMgr.GetStageNo(m_stageName);
	LoadAndCreateObject(stageNo, player, gateMgr);
	LoadGimmickLinkInfo(stageNo);
	LoadFloorMoveInfo(stageNo);
	LoadCheckPoint(stageNo);
}

void StageManager::Update()
{
	for (const auto& obj : m_objs)
	{
		obj->Update();
	}
}

void StageManager::Draw() const
{
	for (const auto& obj : m_objs)
	{
		obj->Draw();
	}
}

void StageManager::End()
{
	for (auto& obj : m_objs)
	{
		obj->End();
	}
}

void StageManager::Restart()
{
	for (auto& obj : m_objs)
	{
		obj->Restart();
	}
}

void StageManager::UpdateCheckPoint(int checkNo)
{
	auto& saveDataMgr = SaveDataManager::GetInstance();
	saveDataMgr.UpdateCheckPoint(m_stageName, checkNo);
}

const Vec3& StageManager::GetCheckPoint() const
{
	auto& saveDataMgr = SaveDataManager::GetInstance();
	auto cp = saveDataMgr.GetCpNo(m_stageName);
	return m_checkPoints.at(cp)->GetPos();
}

void StageManager::LoadAndCreateObject(int stageNo, Player* player, GateManager* gateMgr)
{
	SetUseASyncLoadFlag(false);

	std::wostringstream path;
	path << BASE_PATH << MODEL_INFO_PATH << stageNo << EXTENSION;
	int handle = FileRead_open(path.str().c_str());

	if (handle != 0)
	{
		int size;
		FileRead_read(&size, sizeof(int), handle);

		for (int i = 0; i < size; ++i)
		{
			// タグ読み込み
			uint8_t tagSize = 0;
			FileRead_read(&tagSize, sizeof(tagSize), handle);
			std::string tag;
			tag.resize(tagSize);
			FileRead_read(tag.data(), tagSize, handle);
			// データ読み込み
			ModelData data;
			FileRead_read(&data, sizeof(data), handle);

			// 判定データ読み込み
			std::list<Tuple<MyEngine::ColKind, MyEngine::ColliderBase*>> list;
			int colSize = 0;
			FileRead_read(&colSize, sizeof(int), handle);
			for (int i = 0; i < colSize; ++i)
			{
				MyEngine::ColKind kind;
				FileRead_read(&kind, sizeof(ColKind), handle);
				const auto& func = m_createFunc.at(kind);
				auto res = (this->*func)(handle, data);
				list.emplace_back(Tuple<MyEngine::ColKind, MyEngine::ColliderBase*>{ kind, res });
			}

			// オブジェクト生成
			std::shared_ptr<Object3DBase> obj;
			bool isGravity = false;
			bool isTrigger = false;
			bool isLoadModel = true;
			if (tag == "Turret")
			{
				Vec3 dir;
				FileRead_read(&dir, sizeof(Vec3), handle);
				auto turret = std::make_shared<Turret>();
				turret->Init(dir, player);
				obj = turret;
			}
			else if (tag == "HandObj")
			{
				obj = std::make_shared<HandObject>();
				isGravity = true;
			}
			else if (tag == "LaserLaunchPad")
			{
				Vec3 dir;
				FileRead_read(&dir, sizeof(Vec3), handle);
				auto launchPad = std::make_shared<LaserLaunchPad>(gateMgr);
				launchPad->Init(dir);
				obj = launchPad;
				isTrigger = true;
			}
			else if (tag == "LaserCatcher")
			{
				obj = std::make_shared<LaserCatcher>();
				isTrigger = true;
			}
			else if (tag == "FloorMove")
			{
				obj = std::make_shared<MoveFloorManager>();
				isLoadModel = false;
			}
			else if (tag == "Piston")	obj = std::make_shared<Piston>();
			else if (tag == "Button")	obj = std::make_shared<Button>();
			else if (tag == "Door")		obj = std::make_shared<Door>();
			else						obj = std::make_shared<Object3DBase>(MyEngine::Collidable::Priority::STATIC, OBJECT_TAG.at(tag));

			if (isLoadModel) obj->LoadModel(MODEL_ID.at(tag));
			obj->Init(data.pos, data.scale * 0.01f, data.rot, list, isGravity);
			m_objs.emplace_back(obj);
		}

		FileRead_close(handle);
	}
	else
	{
		assert(false && "データのファイルパスが違います");
	}

	SetUseASyncLoadFlag(true);
}

void StageManager::LoadGimmickLinkInfo(int stageNo)
{
	SetUseASyncLoadFlag(false);

	std::wostringstream path;
	path << BASE_PATH << GIMMICK_INFO_PATH << stageNo << EXTENSION;
	int handle = FileRead_open(path.str().c_str());

	if (handle != 0)
	{
		int size;
		FileRead_read(&size, sizeof(int), handle);

		for (int i = 0; i < size; ++i)
		{
			// 送る側のオブジェクト番号取得
			int gimmickNo;
			FileRead_read(&gimmickNo, sizeof(int), handle);
			// 受け取る側のオブジェクト番号取得
			int linkNo;
			FileRead_read(&linkNo, sizeof(int), handle);

			auto gimmick = std::dynamic_pointer_cast<GimmickSendObject>(m_objs.at(gimmickNo));
			auto link = std::dynamic_pointer_cast<GimmickLinkObject>(m_objs.at(linkNo));

			gimmick->SetLinkObject(link.get());
		}

		FileRead_close(handle);
	}
	else
	{
		assert(false && "ギミックリンクデータのファイルパスが違います");
	}

	SetUseASyncLoadFlag(true);
}

void StageManager::LoadFloorMoveInfo(int stageNo)
{
	SetUseASyncLoadFlag(false);

	std::wostringstream path;
	path << BASE_PATH << FLOOR_MOVE_INFO_PATH << stageNo << EXTENSION;
	int handle = FileRead_open(path.str().c_str());

	if (handle != 0)
	{
		int size;
		FileRead_read(&size, sizeof(int), handle);

		for (int i = 0; i < size; ++i)
		{
			// ポジション数読み込み
			int num;
			FileRead_read(&num, sizeof(int), handle);
			// ポジションデータ読み込み
			std::vector<Vec3> posTable(num);
			FileRead_read(posTable.data(), sizeof(Vec3) * num, handle);
			// オブジェクト番号取得
			int index;
			FileRead_read(&index, sizeof(int), handle);

			auto obj = m_objs.at(index);
			if (obj->GetTag() == ObjectTag::PISTON)
			{
				auto piston = std::dynamic_pointer_cast<Piston>(obj);
				piston->SetMoveRange(posTable[0], posTable[1]);
			}
			else
			{
				auto moveFloorMgr = std::dynamic_pointer_cast<MoveFloorManager>(obj);
				moveFloorMgr->SetCheckPtTable(posTable);
			}
		}

		FileRead_close(handle);
	}
	else
	{
		assert(false && "動く床データのファイルパスが違います");
	}

	SetUseASyncLoadFlag(true);
}

void StageManager::LoadCheckPoint(int stageNo)
{
	SetUseASyncLoadFlag(false);

	std::wostringstream path;
	path << BASE_PATH << CHECK_POINT_INFO_PATH << stageNo << EXTENSION;
	int handle = FileRead_open(path.str().c_str());

	if (handle != 0)
	{
		int size;
		FileRead_read(&size, sizeof(int), handle);

		for (int i = 0; i < size; ++i)
		{
			// データ読み込み
			Vec3 pos;
			Quaternion rot;
			float size;
			float radius;

			FileRead_read(&pos, sizeof(Vec3), handle);
			FileRead_read(&rot, sizeof(Quaternion), handle);
			FileRead_read(&size, sizeof(float), handle);
			FileRead_read(&radius, sizeof(float), handle);

			auto obj = std::make_shared<CheckPoint>(*this, i);
			obj->Init(pos, rot, size, radius);

			m_checkPoints.emplace_back(obj);
		}

		FileRead_close(handle);
	}
	else
	{
		assert(false && "チェックポイントデータのファイルパスが違います");
	}

	SetUseASyncLoadFlag(true);
}

MyEngine::ColliderBase* StageManager::LoadBoxColInfo(int handle, const ModelData& data)
{
	auto col = new MyEngine::ColliderBox;
	FileRead_read(&col->center, sizeof(Vec3), handle);
	FileRead_read(&col->size, sizeof(Vec3), handle);
	FileRead_read(&col->norm, sizeof(Vec3), handle);
	FileRead_read(&col->rotation, sizeof(Quaternion), handle);
	FileRead_read(&col->isTrigger, sizeof(bool), handle);
	return col;
}

MyEngine::ColliderBase* StageManager::LoadSphereColInfo(int handle, const ModelData& data)
{
	auto col = new MyEngine::ColliderSphere;
	FileRead_read(&col->center, sizeof(Vec3), handle);
	FileRead_read(&col->radius, sizeof(float), handle);
	FileRead_read(&col->isTrigger, sizeof(bool), handle);
	return col;
}
