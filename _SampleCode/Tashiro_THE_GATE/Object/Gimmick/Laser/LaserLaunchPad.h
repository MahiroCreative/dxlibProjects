﻿#pragma once
#include "Object/Object3DBase.h"

class GateManager;
class LaserBullet;

class LaserLaunchPad : public Object3DBase
{
public:
	LaserLaunchPad(const GateManager* gateMgr);
	~LaserLaunchPad();

	void Init(const Vec3& dir);
	void Restart() override;
	void Update() override;

	void DestoryBullet();
	void OnClear() { m_isClear = true; }

private:
	const GateManager* m_gateMgr;
	std::shared_ptr<LaserBullet> m_bullet;

	Vec3 m_firingDir;

	int m_createCount;

	bool m_isClear;
};

