#include "LaserCatcher.h"
#include "Collider/ColliderSphere.h"
#include "Object/Gimmick/GimmickLinkObject.h"

LaserCatcher::LaserCatcher() :
	GimmickSendObject(Priority::STATIC, ObjectTag::LASER_CATCHER)
{
}

LaserCatcher::~LaserCatcher()
{
}

void LaserCatcher::OnTriggerEnter(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	MyEngine::Collidable::OnTriggerEnter(colider, colIndex, hitInfo);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::LASER_BULLET)
	{
		m_linkObj->OnGimmick();
	}
}
