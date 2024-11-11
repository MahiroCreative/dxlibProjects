#include "Player.h"
#include "Game.h"
#include "File.h"
#include "MathHelp.h"
#include "Easing.h"
#include "Input.h"
#include "CommandList.h"
#include "Application.h"
#include "SoundManager.h"
#include "AnimController.h"
#include "PlayerCamera.h"
#include "Physics.h"
#include "Collider/ColliderSphere.h"
#include "Collider/ColliderCapsule.h"
#include "Gate/GateManager.h"
#include "Gate/GateBullet.h"
#include "Gate/Gate.h"
#include "Object/HandObject.h"
#include "DebugDraw.h"

namespace
{
	// ファイルID
	const wchar_t* const FILE_PALYER = L"M_Player";
	const wchar_t* const FILE_HP_FRAME = L"I_HpFrame";
	const wchar_t* const FILE_BASE_HP_BAR = L"I_BaseHpBar";
	const wchar_t* const FILE_NOW_HP_BAR = L"I_NowHpBar";
	const wchar_t* const FILE_HIT_HP_BAR = L"I_HitHpBar";
	const wchar_t* const FILE_LANDING = L"S_Landing";
	const wchar_t* const FILE_WALK = L"S_Walk";
	const wchar_t* const FILE_SHOT = L"S_PlayerShot";

	// アニメーション関連
	const wchar_t* const ANIM_INFO_PATH = L"Data/Master/AnimPlayerMaster.csv";
	const wchar_t* const ANIM_IDLE = L"Idle";
	const wchar_t* const ANIM_WALK = L"Walk";
	const wchar_t* const ANIM_JUMP = L"Jump";
	const wchar_t* const ANIM_AERIAL = L"Aerial";
	const wchar_t* const ANIM_LANDING = L"Landing";
	const wchar_t* const ANIM_DEATH = L"Death";

	// 画像サイズ
	constexpr float FILE_SIZE = 0.35f;
	// HPフレームの描画位置
	constexpr int DRAW_HP_FRME_X = 157;
	constexpr int DRAW_HP_FRME_Y = 70;
	// HPバーの描画位置
	constexpr int DRAW_HP_BAR_X = 157 + 36;
	constexpr int DRAW_HP_BAR_Y = 70;
	// 揺らす大きさ
	constexpr int SHAKE_SIZE = 5;

	// FIXME: ここらへんの情報は一部CSVで管理するようにするかも
	constexpr float HAND_RADIUS = 2.0f;	// 物を持てる範囲
	constexpr float HAND_DIS = 4.0f;	// 物を持つ当たり判定の中心との距離

	constexpr float MODEL_SCALE = 0.02f;

	constexpr float RADIUS = 1.0f;	// 当たり半径
	constexpr float SPEED = 0.2f;	// 移動速度
	constexpr float JUMP_POWER = 0.55f;	// ジャンプ力
	constexpr int SHOT_INTERVAL = 60;	// 撃つ間隔
	constexpr int MAX_HP = 100;	// 最大HP
	constexpr int RECEVER_WAIT_FRAME = 120;	// HP回復までの待機フレーム

	// HPバーを揺らすフレーム
	constexpr int SHKE_HP_BAR_FRAME = 30;
	// 減少HPを減らし始めるまでのフレーム
	constexpr int START_DECREASE_PRE_HP_BAR_FRAME = 10;
}

Player::Player(const std::shared_ptr<PlayerCamera>& camera, const std::shared_ptr<GateManager>& gateMgr) :
	Object3DBase(Priority::HIGH, ObjectTag::PALYER),
	m_updateFunc(&Player::IdleUpdate),
	m_camera(camera),
	m_gateMgr(gateMgr),
	m_handObj(nullptr),
	m_nowState(State::IDLE),
	m_hp(MAX_HP),
	m_preHp(MAX_HP),
	m_receverFrame(0),
	m_shotInteval(0),
	m_shakeHpBarFrame(-1),
	m_isOneHand(false),
	m_isDeath(false),
	m_isRecever(false),
	m_isGround(false),
	m_isAddThroughTag(false),
	m_isCatch(false),
	m_isWarp(false)
{
}

Player::~Player()
{
}

void Player::Init(bool isOneHand)
{
	LoadModel(FILE_PALYER);
	auto& fileMgr = FileManager::GetInstance();
	m_files[FILE_HP_FRAME] = fileMgr.Load(FILE_HP_FRAME);
	m_files[FILE_BASE_HP_BAR] = fileMgr.Load(FILE_BASE_HP_BAR);
	m_files[FILE_NOW_HP_BAR] = fileMgr.Load(FILE_NOW_HP_BAR);
	m_files[FILE_HIT_HP_BAR] = fileMgr.Load(FILE_HIT_HP_BAR);
	m_files[FILE_LANDING] = fileMgr.Load(FILE_LANDING);
	m_files[FILE_WALK] = fileMgr.Load(FILE_WALK);
	m_files[FILE_SHOT] = fileMgr.Load(FILE_SHOT);

	m_anim = std::make_shared<AnimController>();
	m_anim->Init(ANIM_INFO_PATH, m_modelHandle, ANIM_IDLE);

	OnEntryPhysics();
	m_rigid.SetPos(Vec3(36, 50, 90));
//	m_rigid.SetPos(Vec3(110, 1, -6));
	m_updateFunc = &Player::IdleUpdate;
	m_pivot.y = -RADIUS - 1.0f;
	m_scale *= MODEL_SCALE;

	auto col = std::dynamic_pointer_cast<MyEngine::ColliderCapsule>(CreateCollider(MyEngine::ColKind::CAPSULE));
	col->radius = RADIUS;
	col->size = 2.0f;
	col->dir = Vec3::Up();
	m_centerCol = std::make_shared<MyEngine::ColliderSphere>();
	m_centerCol->radius = 1.0f;

	m_handCol = std::make_shared<MyEngine::ColliderSphere>();
	m_handCol->radius = HAND_RADIUS;
	m_handCol->isTrigger = true;

	m_isOneHand = isOneHand;

	m_hp = MAX_HP;
	m_preHp = MAX_HP;

	m_shakeHpBarFrame = -1;
}

void Player::Restart(const Vec3& pos)
{
	// アニメーション初期化
	m_anim->Change(ANIM_IDLE, true, false, false);

	// 位置変更
	m_rigid.SetPos(pos);
//	m_rigid.SetPos(Vec3(-6, 1, -6));

	// ものを持っていれば離す
	if (m_isCatch)
	{
		m_handObj->EndHand();
		m_handCol = nullptr;
		m_isCatch = false;
	}

	// 体力初期化
	m_hp = MAX_HP;
	m_preHp = MAX_HP;

	m_shakeHpBarFrame = -1;

	// 更新先変更
	m_updateFunc = &Player::IdleUpdate;
	// 死亡していないことに
	m_isDeath = false;
}

void Player::Update()
{
	// 死んでいない場合更新
	if (!m_isDeath)
	{
		--m_shotInteval;
		HandUpdate();
		RecoverHpUpdate();
	}
	HpBarUpdate();
	(this->*m_updateFunc)();
	AnimUpdate();
	m_rotation = Easing::Slerp(m_rotation, m_nextRot, 0.2f);

	m_camera->Update(m_rigid.GetPos());
#ifdef _DEBUG
	const auto& pos = m_rigid.GetPos();
	const auto& vel = m_rigid.GetVelocity();
	printf("PlayerPos:(%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
	printf("PlayerVel:(%.2f, %.2f, %.2f)", vel.x, vel.y, vel.z);
#endif
}

void Player::Draw() const
{
	// FIXME: モデルの描画が邪魔だから一時的に消している
	Object3DBase::Draw();
}

void Player::DrawHpUI() const
{
	// 画像サイズ取得
	int w, h;
	GetGraphSize(m_files.at(FILE_BASE_HP_BAR)->GetHandle(), &w, &h);
	// 大きさ変更
	w = static_cast<int>(w * FILE_SIZE);
	h = static_cast<int>(h * FILE_SIZE);

	int shakeX = 0;
	int shakeY = 0;
	// バーを揺らす場合
	if (m_shakeHpBarFrame > 0)
	{
		// サイズ調整
		int size = static_cast<int>((static_cast<float>(m_shakeHpBarFrame) / SHKE_HP_BAR_FRAME) * SHAKE_SIZE);
		// 揺らす範囲をランダムで取得
		auto& app = Application::GetInstance();
		shakeX = app.GetRand(0, size);
		shakeY = app.GetRand(0, size);
	}

	// フレームの描画
	DrawRotaGraphFast(DRAW_HP_FRME_X + shakeX, DRAW_HP_FRME_Y + shakeY, FILE_SIZE, 0.0f, m_files.at(FILE_HP_FRAME)->GetHandle(), true);
	// ベースとなるHPバーを描画
	DrawRotaGraphFast(DRAW_HP_BAR_X + shakeX, DRAW_HP_BAR_Y + shakeY, FILE_SIZE, 0.0f, m_files.at(FILE_BASE_HP_BAR)->GetHandle(), true);
	// 下二つのバーの描画位置を取得
	int x = DRAW_HP_BAR_X - static_cast<int>(w * 0.5f) + shakeX;
	int y = DRAW_HP_BAR_Y - static_cast<int>(h * 0.5f) + shakeY;
	// 減少HPの割合を取得
	float rate = m_preHp / static_cast<float>(MAX_HP);
	// 減少HPバーを割合を考慮して描画
	DrawExtendGraph(x, y, x + static_cast<int>(w * rate), y + h, m_files.at(FILE_HIT_HP_BAR)->GetHandle(), true);
	// 現在HPの割合を取得
	rate = m_hp / static_cast<float>(MAX_HP);
	// 現在HPバーを割合を考慮して描画
	DrawExtendGraph(x, y, x + static_cast<int>(w * rate), y + h, m_files.at(FILE_NOW_HP_BAR)->GetHandle(), true);
}

void Player::OnDamage(int damage)
{
	// 減少HPが現在のHP未満なら代入する
	if (m_preHp < m_hp)
	{
		m_preHp = m_hp;
	}
	m_shakeHpBarFrame = SHKE_HP_BAR_FRAME;

	m_hp -= damage;
	if (m_hp <= 0)
	{
		OnDeath();
	}
	m_receverFrame = RECEVER_WAIT_FRAME;
	m_isRecever = true;
}

std::shared_ptr<Camera> Player::GetCamera() const
{
	return m_camera;
}

void Player::OnCollideEnter(Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	MyEngine::Collidable::OnCollideEnter(colider, colIndex, hitInfo);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::FLOOR || tag == ObjectTag::FLOOR_MOVE)
	{
		OnLanding();
	}
}

void Player::OnCollideStay(Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	MyEngine::Collidable::OnCollideStay(colider, colIndex, hitInfo);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::FLOOR_MOVE)
	{
		auto vel = m_rigid.GetVelocity();
		vel.y = 0;
		m_rigid.SetVelocity(vel);
		auto pos = m_rigid.GetPos();
		pos += colider->GetVelocity();
		m_rigid.SetPos(pos);
	}
}

void Player::OnTriggerStay(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	MyEngine::Collidable::OnTriggerStay(colider, colIndex, hitInfo);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::GATE)
	{
		ThroughTagUpdate();
		if (!m_isAddThroughTag) return;
		auto gate = dynamic_cast<Gate*>(colider);
		// ワープ判定
		if (gate->CheckWarp(m_rigid.GetPos()))
		{
			auto preVelDir = m_rigid.GetDir();

			gate->OnWarp(m_rigid.GetPos(), m_rigid, true);

			m_camera->OnWarp(preVelDir, m_rigid.GetDir(), m_rigid.GetPos());
				
			OnAerial();
				
			// 現在持っているゲートによるスルータグを消す
			m_throughTag.pop_back();
			// ペアのゲートのスルータグに変更する
			m_throughTag.emplace_back(gate->GetPairGate()->GetHitObjectTag());
		}
	}
}

void Player::OnTriggerExit(MyEngine::Collidable* colider, int colIndex, const MyEngine::CollideHitInfo& hitInfo)
{
	MyEngine::Collidable::OnTriggerExit(colider, colIndex, hitInfo);

	auto tag = colider->GetTag();
	if (tag == ObjectTag::GATE)
	{
		ThroughTagUpdate();
	}
}

void Player::HandUpdate()
{
	m_handCol->center = m_camera->GetInfo().front * HAND_DIS;

	auto& phsyics = MyEngine::Physics::GetInstance();
	const auto& res = phsyics.GetHitObject(m_rigid.GetPos(), m_handCol.get(), ObjectTag::HAND_OBJ);
	if (!res.empty())
	{
		auto& input = Input::GetInstance();
		if (input.IsTriggerd(Command::BTN_HAND))
		{
			OnHand(res[0].col);
		}
	}

	if (m_isCatch)
	{
		m_handObj->SetPos(m_rigid.GetPos() + m_handCol->center);
		m_handObj->ZeroGravity();
	}
#ifdef _DEBUG
	auto& debug = MyEngine::DebugDraw::GetInstance();
	debug.DrawSphere(m_rigid.GetPos() + m_handCol->center, m_handCol->radius, 0x0000ff, false);
#endif
}

void Player::RecoverHpUpdate()
{
	// 回復しきっていたら処理なし
	if (!m_isRecever) return;

	// 回復待機時間のを減らす
	--m_receverFrame;
	// 回復待機中なら終了
	if (m_receverFrame > 0) return;

	// HP増加
	++m_hp;
	// 最大HPを超えたら修正して回復終了とする
	if (m_hp > MAX_HP)
	{
		m_hp = MAX_HP;
		m_isRecever = false;
	}
}

void Player::HpBarUpdate()
{
	// 揺らし時間内なら時間を減らしていく
	if (m_shakeHpBarFrame > -1)
	{
		--m_shakeHpBarFrame;
	}

	// 減少HPが現在のHPより大きく、揺らし時間が一定時間経っていれば減少HPを減らしていく
	if (m_preHp > m_hp && m_shakeHpBarFrame < SHKE_HP_BAR_FRAME - START_DECREASE_PRE_HP_BAR_FRAME)
	{
		--m_preHp;
		// HPより小さくなったらHPと同じに修正する
		if (m_preHp < m_hp)
		{
			m_preHp = m_hp;
		}
	}
}

void Player::ThroughTagUpdate()
{
	// ゲートを両方とも生成してなければ処理なし
	if (!m_gateMgr->IsCreateBothGates()) return;
	
#ifdef _DEBUG
	auto& debug = MyEngine::DebugDraw::GetInstance();
	debug.DrawSphere(m_rigid.GetPos(), m_centerCol->radius, 0x00ff00, true);
#endif

	auto& physics = MyEngine::Physics::GetInstance();
	// 中心とゲートとの当たり判定
	auto res = physics.GetHitObject(m_rigid.GetPos(), m_centerCol.get(), ObjectTag::GATE, MyEngine::PreHitInfo{}, true);
	if (res.empty() && m_isAddThroughTag)
	{
		m_isAddThroughTag = false;
		m_throughTag.pop_back();
	}
	else if (!res.empty() && !m_isAddThroughTag)
	{
		m_isAddThroughTag = true;
		auto gate = dynamic_cast<Gate*>(res[0].col);
		m_throughTag.emplace_back(gate->GetHitObjectTag());
	}
}

void Player::AnimUpdate()
{
	if (m_nowState == State::MOVE)
	{
		auto sqSpeed = m_rigid.GetVelocity().SqLength();
		auto rate = (sqSpeed / (SPEED * SPEED)) * 0.7f + 0.3f;
		m_anim->Update(rate);
	}
	else
	{
		m_anim->Update();
	}
}

void Player::IdleUpdate()
{
	auto& input = Input::GetInstance();
	const auto& trigger = input.GetTriggerData();
	// 左スティックが入力されたら移動状態に遷移
	if (trigger.LStick.SqLength() > 0.0f)
	{
		OnWalk();
		return;
	}
	// ジャンプに遷移
	if (input.IsTriggerd(Command::BTN_JUMP))
	{
		OnJump();
	}
	// トリガーが入力されたら発射
	if (trigger.LT > 0.0f || trigger.RT > 0.0f)
	{
		OnShot();
	}
}

void Player::WalkUpdate()
{
	auto& input = Input::GetInstance();
	const auto& trigger = input.GetTriggerData();
	// ジャンプに遷移
	if (input.IsTriggerd(Command::BTN_JUMP))
	{
		OnJump();
		SoundManager::GetInstance().Stop(m_files.at(FILE_WALK)->GetHandle());
	}
	// 左スティックが入力されている間は移動
	else if (trigger.LStick.SqLength() > 0.0f)
	{
		// Y軸を無視したカメラの正面方向・右方向を取得
		auto& cInfo = m_camera->GetInfo();
		auto cameraFront = cInfo.front;
		cameraFront.y = 0;
		cameraFront.Normalize();
		// カメラの向いている方向に合わせて移動ベクトルを作成
		Vec3 newVel;
		newVel = cameraFront * trigger.LStick.y + cInfo.right * trigger.LStick.x;
		// 次の回転方向のベクトルを取得
		m_nextRot = Quaternion::GetQuaternion(Vec3::Back(), newVel);
		// 移動ベクトルを移動スピードの長さに変換して、y軸を重力加速度に変更する
		newVel *= SPEED;
		newVel.y = m_rigid.GetVelocity().y;
		m_rigid.SetVelocity(newVel);
	}
	// 入力されていなかったらアイドル状態に遷移
	else
	{
		OnIdle();
		SoundManager::GetInstance().Stop(m_files.at(FILE_WALK)->GetHandle());
	}
}

void Player::JumpUpdate()
{
	if (m_anim->IsLoop())
	{
		OnAerial();
	}
}

void Player::AerialUpdate()
{
	// とくに処理なし
}

void Player::LandingUpdate()
{
	auto& input = Input::GetInstance();
	const auto& trigger = input.GetTriggerData();
	// 左スティックが入力されたら移動状態に遷移
	if (trigger.LStick.SqLength() > 0.0f)
	{
		OnWalk();
	}
	// 何もせずにアニメーションがループ完了したら待機状態に遷移
	else if (m_anim->IsLoop())
	{
		OnIdle();
	}
}

void Player::DeathUpdate()
{
	// 特になし
}

void Player::OnIdle()
{
	// 速度ゼロ
	m_rigid.SetVelocity(Vec3());
	m_anim->Change(ANIM_IDLE);
	m_updateFunc = &Player::IdleUpdate;
	m_nowState = State::IDLE;
}

void Player::OnWalk()
{
	SoundManager::GetInstance().PlaySe(m_files.at(FILE_WALK)->GetHandle());
	m_anim->Change(ANIM_WALK);
	m_updateFunc = &Player::WalkUpdate;
	m_nowState = State::MOVE;
}

void Player::OnJump()
{
	if (!m_isGround) return;

	auto vel = m_rigid.GetVelocity();
	vel.y = JUMP_POWER;
	m_rigid.SetVelocity(vel);
	m_isGround = false;
	m_anim->Change(ANIM_JUMP, true, true);
	m_updateFunc = &Player::JumpUpdate;
	m_nowState = State::JUMP;
}

void Player::OnAerial()
{
	m_isGround = false;
	m_anim->Change(ANIM_AERIAL);
	m_updateFunc = &Player::AerialUpdate;
	m_nowState = State::AERIAL;
}

void Player::OnLanding()
{
	if (m_isGround) return;

	auto& sndMgr = SoundManager::GetInstance();
	sndMgr.PlaySe(m_files.at(FILE_LANDING)->GetHandle());
	m_isGround = true;
	m_rigid.SetVelocity(Vec3());
	m_anim->Change(ANIM_LANDING, true, true);
	m_updateFunc = &Player::LandingUpdate;
	m_nowState = State::LANDING;
}

void Player::OnDeath()
{
	if (m_isDeath) return;

	m_isDeath = true;
	m_rigid.SetVelocity(Vec3());
	m_anim->Change(ANIM_DEATH, true, true);
	m_updateFunc = &Player::DeathUpdate;
	m_nowState = State::DEATH;
}

void Player::OnShot()
{
	// ショット待機時間なら撃たない
	if (m_shotInteval > 0) return;

	auto& input = Input::GetInstance();
	const auto& trigger = input.GetTriggerData();
	bool isCreate = false;
	GateKind kind;
	// 左トリガーが押されていたらゲートAを撃つ
	if (trigger.LT > 0.0f)
	{
		isCreate = true;
		kind = GateKind::Orange;
	}
	// 片手ステージではないかつ左トリガーが押されていたらゲートBを撃つ
	else if (!m_isOneHand && trigger.RT > 0.0f)
	{
		isCreate = true;
		kind = GateKind::Blue;
	}
	// 弾の生成
	if (isCreate)
	{
		auto& sndMgr = SoundManager::GetInstance();
		sndMgr.PlaySe(m_files.at(FILE_SHOT)->GetHandle());
		// インターバルを初期化
		m_shotInteval = SHOT_INTERVAL;
		// 生成
		auto bullet = std::make_shared<GateBullet>(m_gateMgr, kind);
		// カメラの向いている方向に弾を進ませる
		bullet->Init(m_rigid.GetPos(), m_camera->GetInfo().front);
		// 追加
		m_gateMgr->AddBullet(bullet);
	}
}

void Player::OnHand(MyEngine::Collidable* obj)
{
	if (m_isCatch)
	{
		m_handObj->EndHand();
		m_handObj = nullptr;
	}
	else
	{
		m_handObj = dynamic_cast<HandObject*>(obj);
		m_handObj->OnHnad();
	}

	m_isCatch = !m_isCatch;
}
