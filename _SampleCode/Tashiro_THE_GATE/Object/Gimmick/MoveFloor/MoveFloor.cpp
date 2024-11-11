#include "MoveFloor.h"
#include "MoveFloorManager.h"

namespace
{
	constexpr float MOVE_SPEED = 0.2f;
}

MoveFloor::MoveFloor(MoveFloorManager& mgr) :
	Object3DBase(Priority::STATIC, ObjectTag::FLOOR_MOVE),
	m_mgr(mgr),
	m_nowCheckPt(0),
	m_isEnd(false),
	m_isStop(false)
{
}

MoveFloor::~MoveFloor()
{
}

void MoveFloor::InitDir(const Vec3& dir)
{
	m_rigid.SetVelocity(dir * MOVE_SPEED);
}

void MoveFloor::Update()
{
	// 次のチェックポイントまで動いていなければ終了
	if (!m_mgr.CheckMovedNextCheckPt(m_rigid.GetPos(), m_nowCheckPt)) return;
	// チェックポイントを次へ
	++m_nowCheckPt;
	// 全てのチェックポイント-1分を通っていたら終了
	if (m_nowCheckPt >= m_mgr.GetCheckPtNum() - 1)
	{
		End();
		m_isEnd = true;
		return;
	}
	// 位置の補正
	const auto& pos = m_mgr.GetCheckPtPos(m_nowCheckPt);
	m_rigid.SetPos(pos);
	// 次のチェックポイントまでの移動ベクトルに変更
	const auto& dir = m_mgr.GetMoveDir(pos, m_nowCheckPt + 1);
	m_rigid.SetVelocity(dir * MOVE_SPEED);
}

void MoveFloor::StopMove()
{
	// 止まっていれば処理しない
	if (m_isStop) return;
	m_isStop = true;

	// 移動ベクトルを保存
	m_saveVel = m_rigid.GetVelocity();
	// 速度を0に変更
	m_rigid.SetVelocity(Vec3());
}

void MoveFloor::ReStartMove()
{
	// 動いていれば処理しない
	if (!m_isStop) return;
	m_isStop = false;

	// 保存していた移動ベクトルを代入
	m_rigid.SetVelocity(m_saveVel);
}
