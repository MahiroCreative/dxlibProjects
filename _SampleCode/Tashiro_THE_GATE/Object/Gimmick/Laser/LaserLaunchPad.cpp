#include "LaserLaunchPad.h"
#include "LaserBullet.h"
#include "Collider/ColliderSphere.h"

namespace
{
	// FIXME: 外部化
	constexpr int CREATE_COUNT = 60;
}

LaserLaunchPad::LaserLaunchPad(const GateManager* gateMgr) :
	Object3DBase(Priority::STATIC, ObjectTag::LASER_LAUNCH_PAD),
	m_bullet(nullptr),
	m_gateMgr(gateMgr),
	m_createCount(0),
	m_isClear(false)
{
}

LaserLaunchPad::~LaserLaunchPad()
{
}

void LaserLaunchPad::Init(const Vec3& dir)
{
	m_firingDir = dir;
}

void LaserLaunchPad::Restart()
{
	m_isClear = false;
	m_createCount = 0;
	DestoryBullet();
}

void LaserLaunchPad::Update()
{
	// クリアされていれば処理しない
	if (m_isClear) return;

	// 弾が生成されている場合、弾の更新だけして処理終了
	if (m_bullet)
	{
		m_bullet->Update();
		return;
	}

	// 生成カウント
	++m_createCount;
	if (m_createCount > CREATE_COUNT)
	{
		// 弾生成
		m_bullet = std::make_shared<LaserBullet>(this, m_gateMgr);
		m_bullet->Init(m_rigid.GetPos() + m_firingDir * 5, m_firingDir, 600);
		// カウント初期化
		m_createCount = 0;
	}
}

void LaserLaunchPad::DestoryBullet()
{
	// 弾が存在しない場合は終了
	if (!m_bullet) return;

	m_bullet->End();
	m_bullet = nullptr;
}
