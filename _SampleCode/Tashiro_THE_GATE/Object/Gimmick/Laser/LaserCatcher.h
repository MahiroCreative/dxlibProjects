#pragma once
#include "Object/Gimmick/GimmickSendObject.h"

namespace MyEngine
{
	struct CollideHitInfo;
}
class GimmickLinkObject;

class LaserCatcher : public GimmickSendObject
{
public:
	LaserCatcher();
	virtual ~LaserCatcher();

	virtual void OnTriggerEnter(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo) override;
};
