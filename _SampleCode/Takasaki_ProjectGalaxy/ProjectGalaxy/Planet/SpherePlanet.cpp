﻿#include"MyLib/Physics/ColliderSphere.h"
#include "SpherePlanet.h"
#include"ModelManager.h"

namespace
{
	constexpr float kGroundRadius = 50;
	constexpr float  kGravityRange = 150;
	constexpr float  kGravityPower = 0.98f;

	const char* name = "planet";
	const char* atom = "atomosphere";

}

SpherePlanet::SpherePlanet(Vec3 pos,int color,float gravity,int modelHandle) :Planet(),
m_enemyCount(3),
m_modelHandle(modelHandle)
{
	m_color = color;
	m_rigid->SetPos(pos);
	gravityPower = gravity;
	m_pointLightHandle = CreatePointLightHandle(m_rigid->GetPos().VGet(), 50.0f, 0.0f, 0.0002f, 0.0f);
	MV1SetScale(m_modelHandle, VGet(0.5f, 0.5f, 0.5f));
	MV1SetPosition(m_modelHandle,m_rigid->GetPos().VGet());
}

SpherePlanet::~SpherePlanet()
{
}

void SpherePlanet::Init()
{
	AddCollider(MyEngine::ColliderBase::Kind::Sphere, MyEngine::ColliderBase::ColideTag::Body);//ここで入れたのは重力の影響範囲
	m_colliders.back()->isTrigger = true;
	auto item = dynamic_pointer_cast<MyEngine::ColliderSphere>(m_colliders.back());
	item->radius = kGravityRange;
	AddThroughTag(ObjectTag::Stage);
	AddCollider(MyEngine::ColliderBase::Kind::Sphere, MyEngine::ColliderBase::ColideTag::Body);//マップの当たり判定
	auto item2 = dynamic_pointer_cast<MyEngine::ColliderSphere>(m_colliders.back());
	item2->radius = kGroundRadius;
}

void SpherePlanet::Update()
{
}

void SpherePlanet::Draw()
{

	DrawSphere3D(m_rigid->GetPos().VGet(), kGravityRange, 10, 0xddddff, 0x0000ff, false);
	if (m_isSearch)
	{
		DrawSphere3D(m_rigid->GetPos().VGet(), kGroundRadius, 50, m_color, 0x0000ff, false);
	}
	else
	{
		MV1DrawModel(m_modelHandle);
	}
}

Vec3 SpherePlanet::GravityEffect(std::shared_ptr<Collidable> obj)//成分ごとに計算し、補正後のベクトルを返す
{
	Vec3 objVelocity = obj->PlanetOnlyGetRigid()->GetVelocity();
	
	
	////惑星の中心からy方向に伸ばした線を軸にし、オブジェクトの位置を見て軸と惑星の中心からオブジェクトに向かうベクトルの角度分だけオブジェクトのベロシティのy方向に影響させるという考え方、Xに進みたい場合軸のXを基準に,Zに進みたい場合軸のZを基準
	////Yは法線の角度に回転させる
	Vec3 ansVelocity;
	Vec3 objPos = obj->PlanetOnlyGetRigid()->GetPos();
	Vec3 toObj = objPos-m_rigid->GetPos();
	toObj = toObj.GetNormalized();
	Vec3 GravityDir = toObj * -1;
	obj->SetUpVec(toObj);
	if (obj->IsAntiGravity())
	{

		return objVelocity;
	}

	if (obj->GetTag() == ObjectTag::EnemyAttack)
	{
		return objVelocity;
	}

	//if (obj->GetTag() == ObjectTag::Gorori||obj->GetTag()==ObjectTag::KillerTheSeeker)
	//{
	//	float angleX = DX_PI_F / 2 + atan2(GravityDir.y, GravityDir.x);
	//	float angleZ = DX_PI_F / 2 + atan2(GravityDir.y, GravityDir.z);
	//	ansVelocity = { objVelocity.x * cos(angleX), objVelocity.x * sin(angleX) + objVelocity.z * sin(angleZ), objVelocity.z * cos(angleZ) };
	//	ansVelocity += GravityDir * objVelocity.y;//プレイヤーのジャンプ分のベクトルの加算

	//	ansVelocity += GravityDir * kGravityPower;
	//	obj->SetReverceGravityVec(GravityDir.GetNormalized());

	//	/*VECTOR ANSVECTOR = VGet(objVelocity.x * cos(angleX), objVelocity.x * sin(angleX) + objVelocity.z * sin(angleZ), objVelocity.z * cos(angleZ));
	//	ANSVECTOR = VAdd(ANSVECTOR, objVelocity.y * toObj);
	//	ansVelocity = ANSVECTOR;*/
	//	//ansVelocity -= toObj;
	//	return ansVelocity+ GravityDir * gravityPower*40*((kGravityRange+(obj->GetRigidbody()->GetPos() - m_rigid->GetPos()).Length() -(obj->GetRigidbody()->GetPos()-m_rigid->GetPos()).Length())/ kGravityRange);
	//}

	//重力のみ
	GravityDir = GravityDir * gravityPower * 0.005f * ((kGravityRange + (obj->GetRigidbody()->GetPos() - m_rigid->GetPos()).Length() - (obj->GetRigidbody()->GetPos() - m_rigid->GetPos()).Length()) / kGravityRange) + objVelocity;
	return GravityDir;
}

Vec3 SpherePlanet::GetNormVec(Vec3 pos)
{
	Vec3 norm = pos - m_rigid->GetPos();
	norm.Normalize();
	return norm;
}

void SpherePlanet::OnTriggerEnter(std::shared_ptr<Collidable> colider, MyEngine::ColliderBase::ColideTag tag)
{
	/*if (colider->GetTag() == ObjectTag::Takobo)
	{
		m_enemyCount++;
	}*/
}

void SpherePlanet::OnTriggerExit(std::shared_ptr<Collidable> colider, MyEngine::ColliderBase::ColideTag tag)
{
	if (colider->GetTag() == ObjectTag::Takobo)
	{
		m_enemyCount--;
	}
	if (m_enemyCount <= 0)
	{
		clearFlag = true;
	}
}