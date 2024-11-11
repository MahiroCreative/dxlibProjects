#include "SceneMain.h"
#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "ScreenUtility.h"
#include "CursorUtility.h"
#include "TimeUtility.h"
#include "Input.h"
#include "CommandList.h"
#include "StageDataManager.h"
#include "SaveDataManager.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "SceneStageSelect.h"
#include "File.h"
#include "MyDraw.h"
#include "Collidable.h"
#include "Camera.h"
#include "PlayerCamera.h"
#include "CameraManager.h"
#include "Object/Object3DBase.h"
#include "Object/Player.h"
#include "Object/Stage/StageManager.h"
#include "Object/Gate/GateManager.h"

namespace
{
	enum class RTKind
	{
		GATE_A_TEX,
		GATE_B_TEX,
		TEMP_1,
		TEMP_2,
		MAX,
	};
	enum class DeathUICurrent : int
	{
		CONTINUE,
		RETURN_STAGE_SELECT,
		MAX,
	};

	// ファイルID
	const wchar_t* const FILE_PS_BLEND = L"PS_Blend";
	const wchar_t* const FILE_PS_PIXEL = L"PS_Pixel";
	const wchar_t* const FILE_PS_GATE_POS = L"PS_GatePos";
	const wchar_t* const FILE_TIME_BAR = L"I_TimeBar";
	const wchar_t* const FILE_LOOK_SITE = L"I_LookSite";
	const wchar_t* const FILE_CREATE_GATE_ORANGE = L"I_CreateGateOrange";
	const wchar_t* const FILE_CREATE_GATE_BLUE = L"I_CreateGateBlue";
	const wchar_t* const FILE_NOT_CREATE_GATE_ORANGE = L"I_NotCreateGateOrange";
	const wchar_t* const FILE_NOT_CREATE_GATE_BLUE = L"I_NotCreateGateBlue";

	// ゲートの色
	constexpr unsigned int COLOR_GATE_BLUE = 0x1376b5;
	constexpr unsigned int COLOR_GATE_ORANGE = 0xf19149;
	// タイムの文字の色
	constexpr unsigned int COLOR_TIME_STR = 0xffffff;
	// タイムバー描画位置
	constexpr int DRAW_TIME_X = 132;
	constexpr int DRAW_TIME_Y = 160;
	// タイムバーの画像サイズ
	constexpr float FILE_SIZE_TIME = 0.5f;
	// タイム文字描画位置
	constexpr int DRAW_TIME_STR_X = 32;
	constexpr int DRAW_TIME_STR_Y = 146;
	// タイム文字のフォントサイズ
	constexpr int FONT_SIZE_TIME = 32;
	// サイトの画像サイズ
	constexpr float FILE_SIZE_SITE = 0.09375f;
	// 生成ゲートの画像サイズ
	constexpr float FILE_SIZE_CREATE_GATE = 0.375f;
	// 生成ゲートの回転具合
	constexpr float DRAW_CREATE_GATE_ANGLE = 30 * Game::DEG_2_RAD;
	// 生成ゲートの描画位置(青)
	constexpr int DRAW_CREATE_GATE_BLUE_X = 610;
	constexpr int DRAW_CREATE_GATE_BLUE_Y = 330;
	// 生成ゲートの描画位置(オレンジ)
	constexpr int DRAW_CREATE_GATE_ORANGE_X = 670;
	constexpr int DRAW_CREATE_GATE_ORANGE_Y = 390;
	// 最後に発射したゲートの描画位置(青)
	constexpr int DRAW_SHOT_GATE_BLUE_X = 575;
	constexpr int DRAW_SHOT_GATE_BLUE_Y = 368;
	// 最後に発射したゲートの描画位置(オレンジ)
	constexpr int DRAW_SHOT_GATE_ORANGE_X = 705;
	constexpr int DRAW_SHOT_GATE_ORANGE_Y = 352;
	// 最後に発射したゲートの描画半径
	constexpr int SHOT_GATE_RADIUS = 6;
	// 最後に発射したゲートの線の太さ
	constexpr int SHOT_GATE_LINE_THICKNESS = 2;
}

SceneMain::SceneMain(const wchar_t* const stageName) :
	SceneBase(SceneKind::MAIN),
	m_updateFunc(&SceneMain::MainUpdate),
	m_stageName(stageName),
	m_depthRT(-1),
	m_depthRT2(-1),
	m_time(0),
	m_current(0)
{
	// FIXME: 現段階で光が欲しいためやっている
	int light1 = CreateDirLightHandle(VGet(1, -1, 1));
	int light2 = CreateDirLightHandle(VGet(1, -1, -1));
	int light3 = CreateDirLightHandle(VGet(-1, -1, 1));
	int light4 = CreateDirLightHandle(VGet(-1, -1, -1));
}

void SceneMain::Init()
{
	auto& fileMgr = FileManager::GetInstance();
	auto& stageDataMgr = StageDataManager::GetInstance();
	
	// ファイルの読み込み
	m_files[FILE_PS_BLEND] = fileMgr.Load(FILE_PS_BLEND);
	m_files[FILE_PS_PIXEL] = fileMgr.Load(FILE_PS_PIXEL);
	m_files[FILE_PS_GATE_POS] = fileMgr.Load(FILE_PS_GATE_POS);
	m_files[FILE_TIME_BAR] = fileMgr.Load(FILE_TIME_BAR);
	m_files[FILE_LOOK_SITE] = fileMgr.Load(FILE_LOOK_SITE);
	m_files[FILE_CREATE_GATE_ORANGE] = fileMgr.Load(FILE_CREATE_GATE_ORANGE);
	m_files[FILE_CREATE_GATE_BLUE] = fileMgr.Load(FILE_CREATE_GATE_BLUE);
	m_files[FILE_NOT_CREATE_GATE_ORANGE] = fileMgr.Load(FILE_NOT_CREATE_GATE_ORANGE);
	m_files[FILE_NOT_CREATE_GATE_BLUE] = fileMgr.Load(FILE_NOT_CREATE_GATE_BLUE);
	
	// 画面生成
	m_rtTable.resize(static_cast<int>(RTKind::MAX));
	for (auto& handle : m_rtTable)
	{
		handle = MakeScreen(Game::WINDOW_W, Game::WINDOW_H, true);
	}
	m_depthRT = ScreenUtility::MakeDepthRT(Game::WINDOW_W, Game::WINDOW_H);
	m_depthRT2 = ScreenUtility::MakeDepthRT(Game::WINDOW_W, Game::WINDOW_H);
	// 各マネージャの読み込み
	m_stageMgr = std::make_shared<StageManager>(m_stageName);
	m_cameraMgr = std::make_shared<CameraManager>();
	m_gateMgr = std::make_shared<GateManager>(m_cameraMgr);
	// プレイヤーの生成、初期化
	m_player = std::make_shared<Player>(std::dynamic_pointer_cast<PlayerCamera>(m_cameraMgr->GetCamera(CameraKind::PLAYER)), m_gateMgr);
	m_player->Init(stageDataMgr.IsOneHand(m_stageName));

	// 各マネージャの初期化
	m_stageMgr->Init(m_player.get(), m_gateMgr.get());
	m_gateMgr->SetPlayer(m_player);
	m_gateMgr->CreateGateOnTerrain(m_stageName);

#ifdef USE_CAMERA_COLLIDABLE
	m_cameraMgr->OnEntity(CameraKind::PLAYER, m_gateMgr);
#endif

	// オリジナルシェーダの適用
	MV1SetUseOrigShader(true);
}

void SceneMain::Update(bool isFade)
{
	(this->*m_updateFunc)();
}

void SceneMain::Draw() const
{
	// モデル描画
	if (m_gateMgr->IsCreateBothGates())
	{
		DrawBlend();
	}
	else
	{
		DrawNormal();
	}
	// UI描画
	SetUseZBuffer3D(false);
	DrawCommonUI();
	DrawExistUI();
	DrawDeathUI();
	SetUseZBuffer3D(true);
#ifdef _DEBUG
	auto& stageDataMgr = StageDataManager::GetInstance();
	printf("StageNo:%d\n", stageDataMgr.GetStageNo(m_stageName));
#endif
}

void SceneMain::End()
{
	m_stageMgr->End();
	m_cameraMgr->End();
	m_player->End();

	// オリジナルシェーダの使用終了
	MV1SetUseOrigShader(false);
}

void SceneMain::MainUpdate()
{
	auto& input = Input::GetInstance();
	if (input.IsTriggerd(Command::BTN_OPTION))
	{
		m_scnMgr.OpenOption(SceneKind::MAIN);
		return;
	}
	// 各種更新
	m_gateMgr->Update();
	m_stageMgr->Update();
	m_cameraMgr->Update();
	m_player->Update();
	SaveDataManager::GetInstance().UpdateTime(m_stageName);
	// タイム更新
	++m_time;
#ifdef _DEBUG
	if (input.IsTriggerd(KEY_INPUT_K))
	{
		m_player->OnDamage(99999);
	}
	if (input.IsTriggerd(KEY_INPUT_J))
	{
		m_player->OnDamage(10);
	}
#endif
	// 死亡したら更新先変更
	if (m_player->IsDeath())
	{
		m_updateFunc = &SceneMain::GameOverUpdate;
	}
}

void SceneMain::GameOverUpdate()
{
	m_current = CursorUtility::CursorUp<DeathUICurrent>(m_current, DeathUICurrent::MAX);
	m_current = CursorUtility::CursorDown<DeathUICurrent>(m_current, DeathUICurrent::MAX);

	auto& input = Input::GetInstance();
	if (input.IsTriggerd(Command::BTN_OK))
	{
		if (m_current == static_cast<int>(DeathUICurrent::CONTINUE))
		{
			// 各種リスタート処理
			m_player->Restart(m_stageMgr->GetCheckPoint());
			m_gateMgr->Restart();
			m_gateMgr->CreateGateOnTerrain(m_stageName);
			m_stageMgr->Restart();
			m_updateFunc = &SceneMain::MainUpdate;
		}
		else if (m_current == static_cast<int>(DeathUICurrent::RETURN_STAGE_SELECT))
		{
			auto next = std::make_shared<SceneStageSelect>();
			m_scnMgr.Change(next);
		}
		else
		{
			assert(false);
		}
	}

	// 各種更新(見た目だけ更新)
	m_gateMgr->Update();
	m_stageMgr->Update();
	m_cameraMgr->Update();
	m_player->Update();
}

void SceneMain::DrawNormal() const
{
	// 使用ピクセルシェーダの選択
	SetUsePixelShader(m_files.at(FILE_PS_PIXEL)->GetHandle());

	m_cameraMgr->AppInfo(CameraKind::PLAYER);
	m_gateMgr->DrawGatePos();
	m_stageMgr->Draw();
	m_player->Draw();
}

void SceneMain::DrawBlend() const
{
	// カメラからの画像を描画します
	// その描画した画面をテクスチャとして円形のモデルに描画します
	// その描画したモデル事自身から描画します

	auto rtGateA = m_rtTable[static_cast<int>(RTKind::GATE_A_TEX)];
	auto rtGateB = m_rtTable[static_cast<int>(RTKind::GATE_B_TEX)];
	
	
	DrawGateBlend(rtGateA, CameraKind::GATE_A, CameraKind::GATE_A_FROM_B);
	DrawGateBlend(rtGateB, CameraKind::GATE_B, CameraKind::GATE_B_FROM_A);

	DrawModelBlend(DX_SCREEN_BACK, rtGateA, rtGateB, CameraKind::PLAYER);
}

void SceneMain::DrawCommonUI() const
{
	auto& fontMgr = FontManager::GetInstance();
	auto time = TimeUtility::FrameToTime(m_time);
	DrawRotaGraphFast(DRAW_TIME_X, DRAW_TIME_Y, FILE_SIZE_TIME, 0.0f, m_files.at(FILE_TIME_BAR)->GetHandle(), true);
	DrawFormatStringToHandle(DRAW_TIME_STR_X, DRAW_TIME_STR_Y, COLOR_TIME_STR, fontMgr.GetHandle(FONT_SIZE_TIME), L"%2d:%2d.%2d", time.min, time.sec, time.dec);
	m_player->DrawHpUI();
}

void SceneMain::DrawExistUI() const
{
	// プレイヤーが死んでいる場合は処理終了
	if (m_player->IsDeath()) return;

	
	// サイトの描画
	DrawRotaGraphFast(Game::CENTER_X, Game::CENTER_Y, FILE_SIZE_SITE, 0.0f, m_files.at(FILE_LOOK_SITE)->GetHandle(), true);


	int handle;
	// 青ゲート
	if (m_gateMgr->IsCreate(GateKind::Blue))	handle = m_files.at(FILE_CREATE_GATE_BLUE)->GetHandle();
	else										handle = m_files.at(FILE_NOT_CREATE_GATE_BLUE)->GetHandle();
	DrawRotaGraphFast(DRAW_CREATE_GATE_BLUE_X, DRAW_CREATE_GATE_BLUE_Y, FILE_SIZE_CREATE_GATE, DRAW_CREATE_GATE_ANGLE, handle, true);
	// オレンジゲート
	if (m_gateMgr->IsCreate(GateKind::Orange))	handle = m_files.at(FILE_CREATE_GATE_ORANGE)->GetHandle();
	else										handle = m_files.at(FILE_NOT_CREATE_GATE_ORANGE)->GetHandle();
	DrawRotaGraphFast(DRAW_CREATE_GATE_ORANGE_X, DRAW_CREATE_GATE_ORANGE_Y, FILE_SIZE_CREATE_GATE, DRAW_CREATE_GATE_ANGLE, handle, true);


	int x = DRAW_SHOT_GATE_BLUE_X;
	int y = DRAW_SHOT_GATE_BLUE_Y;
	unsigned int color = COLOR_GATE_BLUE;
	GateKind kind = GateKind::Blue;
	if (m_gateMgr->GetLastShotKind() == GateKind::Orange)
	{
		x = DRAW_SHOT_GATE_ORANGE_X;
		y = DRAW_SHOT_GATE_ORANGE_Y;
		color = COLOR_GATE_ORANGE;
		kind = GateKind::Orange;
	}
	// HACK: 何故かLineThicknessを変更した際に塗りつぶしができない為2個重ねている
	DrawCircle(x, y, SHOT_GATE_RADIUS, color, false, SHOT_GATE_LINE_THICKNESS);
	if (m_gateMgr->IsCreate(kind))  DrawCircle(x, y, SHOT_GATE_RADIUS, color, true);
}

void SceneMain::DrawDeathUI() const
{
	// プレイヤーが生きている場合は処理終了
	if (!m_player->IsDeath()) return;

	const std::vector<std::wstring> STR =
	{
		L"リスタート",
		L"ステージ選択へ"
	};
	DrawBox(640 - 80, 360 - 80, 640 + 80, 360 + 80, 0x000000, true);
	for (int i = 0; i < static_cast<int>(DeathUICurrent::MAX); ++i)
	{
		if (i == m_current)
		{
			DrawBox(640 - 64, 360 - 64 + 32 * i, 640 + 64, 360 - 48 + 32 * i, 0xff0000, true);
		}
		DrawString(640 - 64, 360 - 64 + 32 * i, STR[i].c_str(), 0xffffff);
	}
}

void SceneMain::DrawGateBlend(int rt, CameraKind gate, CameraKind gateFrom) const
{
	auto rtTemp1 = m_rtTable[static_cast<int>(RTKind::TEMP_1)];
	auto rtTemp2 = m_rtTable[static_cast<int>(RTKind::TEMP_2)];

	{
		SetDrawScreen(rtTemp1);
		ClearDrawScreen();
		m_cameraMgr->AppInfo(gateFrom);

		SetUsePixelShader(m_files.at(FILE_PS_PIXEL)->GetHandle());
		m_stageMgr->Draw();
		m_player->Draw();
	}
	for (int i = 0; i < 3; ++i)
	{
		SetDrawScreen(rtTemp2);
		m_cameraMgr->AppInfo(gateFrom);
		SetUsePixelShader(m_files.at(FILE_PS_GATE_POS)->GetHandle());

		if (i == 0)
		{
			ClearDrawScreen();
			m_gateMgr->DrawGate(rtTemp1, rtTemp1);
		}
		else
		{
			m_gateMgr->DrawGate(rtTemp2, rtTemp2);
		}

		SetUsePixelShader(m_files.at(FILE_PS_PIXEL)->GetHandle());
		m_stageMgr->Draw();
		m_player->Draw();
	}
	// ゲートからの画面を描画してあげる
	DrawModelBlend(rt, rtTemp2, rtTemp2, gate);
}

void SceneMain::DrawModelBlend(int rt, int tex1, int tex2, CameraKind camera) const
{
	SetDrawScreen(rt);
	ClearDrawScreen();
	m_cameraMgr->AppInfo(camera);

	SetUsePixelShader(m_files.at(FILE_PS_GATE_POS)->GetHandle());
	m_gateMgr->DrawGate(tex1, tex2);

	SetUsePixelShader(m_files.at(FILE_PS_PIXEL)->GetHandle());
	m_stageMgr->Draw();
	m_player->Draw();
}
