﻿#include "Kuribo.h"
#include"ModelManager.h"

using namespace MyEngine;

namespace
{
	constexpr float kRadius = 5.f;
	constexpr float kSearchRadius = 20.f;
	constexpr float kChaseSpeed = 0.1f;

	constexpr float kAnimFrameSpeed = 30.0f;//アニメーション進行速度

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	constexpr float kFrameParSecond = 60.0f;

	constexpr int kChaseMaxFrame = 200;

	constexpr float kAwayStrength = 0.6f;
	const char* kModelFileName = "Kuribo.mv1";

	constexpr int kAnimationNumAttack = 0;
	constexpr int kAnimationNumIdle = 1;
	constexpr int kAnimationNumFullPowerAttack = 2;
	constexpr int kAnimationNumRoar = 3;
	constexpr int kAnimationNumRun = 4;
	constexpr int kAnimationNumSleep = 5;
	constexpr int kAnimationNumWalk = 6;

	constexpr float kScaleMag = 0.03f;

}

float GetVec2Angle(Vec3 a, Vec3 b)
{
	float cos = Dot(a.GetNormalized(), b.GetNormalized());//ない席は180度まで
	float rad = acos(cos);

#ifdef _DEBUG
	DrawFormatString(0, 125, 0xffffff, "rad(%f),deg(%f)", rad, rad * 180 / DX_PI_F);
#endif

	return rad;
}

Kuribo::Kuribo(Vec3 pos, int moveNum):Enemy(-1,Priority::Low,ObjectTag::Kuribo),
m_attackDir(0,0,1),
m_chaseFrameCount(0)
{
	m_comebackPoint = pos;
	m_rigid->SetPos(pos);
	{
		AddCollider(MyEngine::ColliderBase::Kind::Sphere, MyEngine::ColliderBase::ColideTag::Body);
		auto item = dynamic_pointer_cast<MyEngine::ColliderSphere>(m_colliders.back());
		item->radius = kRadius;
	}
	
#ifdef _DEBUG
	{
		AddCollider(MyEngine::ColliderBase::Kind::Sphere, MyEngine::ColliderBase::ColideTag::Body);
		auto item = dynamic_pointer_cast<MyEngine::ColliderSphere>(m_colliders.back());
		item->radius = kSearchRadius;
		item->isTrigger = true;
		m_searchCol = item;
	}
#endif
	m_moveUpdate = &Kuribo::SearchUpdate;

	m_modelHandle = ModelManager::GetInstance().GetModelData(kModelFileName);
	MV1SetScale(m_modelHandle, VGet(kScaleMag, kScaleMag, kScaleMag));
	ChangeAnim(kAnimationNumIdle);
}

Kuribo::~Kuribo()
{
}

void Kuribo::Init()
{
}

void Kuribo::Update()
{
	(this->*m_moveUpdate)();
	UpdateAnim(m_currentAnimNo);
	//変更前のアニメーション100%
	DxLib::MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//変更後のアニメーション0%
	DxLib::MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
	m_animBlendRate += 0.05f;
	if (m_animBlendRate > 1.0f)
	{
		m_animBlendRate = 1.0f;
	}

}

void Kuribo::SetMatrix()
{
	MV1SetPosition(m_modelHandle, m_rigid->GetPos().VGet());
}

void Kuribo::Draw()
{
	MV1DrawModel(m_modelHandle);
	SetDrawBlendMode(DX_BLENDMODE_MULA, 100);
	DrawSphere3D(m_rigid->GetPos().VGet(), kRadius, 8, 0xffaa00, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_MULA, 100);
	DrawSphere3D(m_rigid->GetPos().VGet(),m_searchCol->radius, 8, 0xffaa00, 0xffffff, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
	DrawLine3D(m_rigid->GetPos().VGet(), (m_rigid->GetPos() + m_attackDir * 30).VGet(), 0x00ff00);
	DrawLine3D(m_rigid->GetPos().VGet(), (m_rigid->GetPos() + m_upVec * 30).VGet(), 0xff0000);
}

void Kuribo::OnCollideEnter(std::shared_ptr<Collidable> colider, MyEngine::ColliderBase::ColideTag tag)
{
	if (colider->GetTag() == ObjectTag::Stage)
	{
		if (m_moveUpdate == &Kuribo::JumpUpdate)
		{
			ChangeAnim(kAnimationNumSleep);
			m_moveUpdate = &Kuribo::DeathUpdate;
		}
	}
	if (colider->GetTag() == ObjectTag::Player)
	{
		if (tag == ColliderBase::ColideTag::Foot)
		{
			MV1SetScale(m_modelHandle, VGet(kScaleMag, 0, kScaleMag));
			m_moveUpdate = &Kuribo::DeathUpdate;
		}
		else if(tag == ColliderBase::ColideTag::Spin)
		{
			m_rigid->SetVelocity(m_attackDir * -kAwayStrength + m_upVec * kAwayStrength * 1.5f);
			m_moveUpdate = &Kuribo::JumpUpdate;
		}
		else
		{

		}
		
	}
}

void Kuribo::OnTriggerStay(std::shared_ptr<Collidable> colider, MyEngine::ColliderBase::ColideTag tag)
{
	if (colider->GetTag() == ObjectTag::Player)
	{
		Vec3 ToVec = colider->GetRigidbody()->GetPos() - m_rigid->GetPos();
		ToVec.Normalize();
		if (GetVec2Angle(m_attackDir, ToVec) <= DX_PI_F /2)
		{
			m_attackDir = colider->GetRigidbody()->GetPos() - m_rigid->GetPos();
			m_attackDir.Normalize();
			m_player = colider;

			m_targetPoint = colider->GetRigidbody()->GetPos();
		}
	}
}

void Kuribo::SearchUpdate()
{
	m_rigid->SetVelocity(Vec3(0, 0, 0));
	if (!m_player.get())return;
	m_rigid->SetVelocity(m_upVec);
	
	m_searchCol->radius = kSearchRadius * 2;
	m_comebackPoint = m_rigid->GetPos();
	ChangeAnim(kAnimationNumWalk);
	m_moveUpdate = &Kuribo::ChaseUpdate;

}

void Kuribo::JumpUpdate()
{
	m_initTime++;
	if (m_initTime >= 60)
	{
		m_isDestroyFlag = true;
	}
}

void Kuribo::ChaseUpdate()
{
	if (!m_player.get())m_chaseFrameCount++;
	//ターゲット位置が正反対の時動かなくなるバグ
	m_attackDir = m_targetPoint - m_rigid->GetPos();
	m_attackDir.Normalize();
	m_rigid->SetVelocity(m_attackDir * kChaseSpeed);
	if (m_chaseFrameCount > kChaseMaxFrame)
	{
		m_chaseFrameCount = 0;
		
		m_moveUpdate = &Kuribo::ComebackUpdate;
		m_player = nullptr;
	}
}

void Kuribo::ComebackUpdate()
{
	Vec3 vec = m_comebackPoint - m_rigid->GetPos();
	vec.Normalize();
	m_rigid->SetVelocity(vec*kChaseSpeed);
	if ((m_comebackPoint - m_rigid->GetPos()).Length() <= 3)
	{
		ChangeAnim(kAnimationNumIdle);
		m_moveUpdate = &Kuribo::SearchUpdate;
	}
	if (!m_player.get())
	{
		m_attackDir = vec;
		return;
	}
	m_rigid->SetVelocity(m_upVec );
	m_searchCol->radius = kSearchRadius;
	m_comebackPoint = m_rigid->GetPos();
	m_moveUpdate = &Kuribo::ChaseUpdate;
}

void Kuribo::DeathUpdate()
{
	m_rigid->SetVelocity(Vec3::Zero());
}

bool Kuribo::UpdateAnim(int attachNo)
{
	//アニメーションが設定されていないので終了
	if (attachNo == -1) return false;

	//アニメーションを進行させる
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);//現在の再生カウント
	now += kAnimFrameSpeed * m_animationSpeed / kFrameParSecond;//アニメーションカウントを進める


	//現在再生中のアニメーションの総カウントを取得する
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);
	bool isLoop = false;
	while (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void Kuribo::ChangeAnim(int animIndex, int speed)
{
	m_animationSpeed = speed;
	//さらに古いアニメーションがアタッチされている場合はこの時点で削除しておく
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevAnimNo);
	}

	//現在再生中の待機アニメーションは変更前のアニメーション扱いに
	m_prevAnimNo = m_currentAnimNo;

	//変更後のアニメーションとして攻撃アニメーションを改めて設定する
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, animIndex, -1, false);

	//切り替えの瞬間は変更前のアニメーションが再生される状態にする
	m_animBlendRate = 0.0f;

	//変更前のアニメーション100%
	DxLib::MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//変更後のアニメーション0%
	DxLib::MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);
}
