#pragma once
#include "Object/Object3DBase.h"

class MoveFloorManager;

class MoveFloor : public Object3DBase
{
public:
	MoveFloor(MoveFloorManager& mgr);
	~MoveFloor();

	void InitDir(const Vec3& dir);
	void Update() override;

	bool IsEnd() const { return m_isEnd; }

	void StopMove();
	void ReStartMove();

private:
	MoveFloorManager& m_mgr;

	Vec3 m_saveVel;
	int m_nowCheckPt;
	bool m_isEnd;
	bool m_isStop;
};

