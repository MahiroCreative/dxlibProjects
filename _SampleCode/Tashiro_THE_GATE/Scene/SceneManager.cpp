#include "SceneManager.h"
#include <DxLib.h>
#ifdef _DEBUG
#include "SceneDebug.h"
#endif
#include "SceneTitle.h"
#include "SceneOption.h"
#include "EffekseerManager.h"
#include "Game.h"
#include "Application.h"
#include "SoundManager.h"

namespace
{
	constexpr int FADE_FRAME = 30;
	constexpr float FADE_SPEED = 1.0f / FADE_FRAME;
}

SceneManager::SceneManager() :
	m_scene(nullptr),
	m_updateFunc(&SceneManager::NormalUpdate),
	m_drawFunc(&SceneManager::DrawNormal),
	m_bgmH(-1),
	m_fadeFunc(&SceneManager::FadeNone),
	m_fadeRate(0.0f),
	m_isFade(false)
{
}

SceneManager::~SceneManager()
{
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager mgr;
	return mgr;
}

void SceneManager::Init()
{
	// 最初のシーンのメモリ確保
#ifdef _DEBUG
	m_scene = std::make_shared<SceneDebug>();
#else
	m_scene = std::make_shared<SceneTitle>();
	m_fadeFunc = &SceneManager::FadeIn;
	m_fadeRate = 1.0f;
	m_isFade = true;
#endif

	m_scene->Init();

	CheckFileLoadingStart();
}

void SceneManager::Update()
{
	if (m_option)
	{
		m_option->Update(false);
		return;
	}
	(this->*m_updateFunc)();
	auto& effMgr = EffekseerManager::GetInstance();
	effMgr.Update();
}

void SceneManager::Draw() const
{
	(this->*m_drawFunc)();
	if (m_option)
	{
		m_option->Draw();
	}

	auto& app = Application::GetInstance();
	int light = app.GetScreenLight();
	int alpha = 255 - light - 50;
	alpha = std::max<int>(alpha, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Game::WINDOW_W, Game::WINDOW_H, 0, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneManager::End()
{
	m_scene->End();
	auto& effMgr = EffekseerManager::GetInstance();
	effMgr.AllStop();
}

void SceneManager::Change(const std::shared_ptr<SceneBase>& next, bool isFade)
{
	if (isFade)
	{
		// フェード処理初期化
		m_fadeRate = 0.0f;
		m_isFade = true;
		// フェードアウトへ
		m_fadeFunc = &SceneManager::FadeOut;

		m_nextScene = next;
	}
	else
	{
		// 終了処理
		m_scene->End();

		// シーン変更
		m_scene = next;
		// 初期化処理
		m_scene->Init();

		CheckFileLoadingStart();
	}
}

void SceneManager::ChangeBgmH(int handle)
{
	m_bgmH = handle;
}

void SceneManager::OpenOption(SceneKind openScene)
{
	// 開いていれば終了
	if (m_option) return;

	auto scene = std::make_shared<SceneOption>();
	scene->Init();
	scene->CheckOpenScene(openScene);
	m_option = scene;
}

void SceneManager::CloseOption()
{
	if (!m_option) return;

	m_option->End();
	m_option = nullptr;
}

SceneKind SceneManager::GetNowSceneKind() const
{
	return m_scene->GetNowKind();
}

void SceneManager::NormalUpdate()
{
	(this->*m_fadeFunc)();
	m_scene->Update(m_isFade);
}

void SceneManager::FileLoadingUpdate()
{
	// TODO: ここにロード終わる野を確認してNormalに代わる処理をかく
	auto num = GetASyncLoadNum();
	if (num == 0)
	{
		m_updateFunc = &SceneManager::NormalUpdate;
		m_drawFunc = &SceneManager::DrawNormal;
	}
}

void SceneManager::DrawNormal() const
{
	m_scene->Draw();

	if (!m_isFade) return;

	// フェード処理
	int alpha = static_cast<int>(Game::ALPHA_VAL * m_fadeRate);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Game::WINDOW_W, Game::WINDOW_H, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneManager::FileLoadingDraw() const
{
	// TODO: ロード中はNowLoadingを出すようにする
	DrawString(600, 360, L"ロード中", 0xffffff);
}

void SceneManager::FadeNone()
{
	// ハンドルが入っていな場合は流さない
	if (m_bgmH > -1)
	{
		auto& snd = SoundManager::GetInstance();
		snd.PlayBgm(m_bgmH);
	}
}

void SceneManager::FadeIn()
{
	m_fadeRate -= FADE_SPEED;

	// フェードイン完了したら
	if (m_fadeRate < 0.0f)
	{
		m_fadeRate = 0.0f;
		// フェード終了
		m_isFade = false;
		// シーンの処理へ
		m_fadeFunc = &SceneManager::FadeNone;
	}

	// ハンドルが入っていな場合は流さない
	if (m_bgmH > -1)
	{
		auto& snd = SoundManager::GetInstance();
		snd.PlayFadeBgm(m_bgmH, 1.0f - m_fadeRate);
	}
}

void SceneManager::FadeOut()
{
	m_fadeRate += FADE_SPEED;

	// フェードアウト完了したら
	if (m_fadeRate > 1.0f)
	{
		// 終了処理
		m_scene->End();
		// シーン変更
		m_scene = m_nextScene;
		// 初期化処理
		m_scene->Init();
		// フェード割合補正
		m_fadeRate = 1.0f;
		// フェードインへ
		m_fadeFunc = &SceneManager::FadeIn;

		CheckFileLoadingStart();
		return;
	}

	// ハンドルが入っていな場合は流さない
	if (m_bgmH > -1)
	{
		auto& snd = SoundManager::GetInstance();
		snd.PlayFadeBgm(m_bgmH, 1.0f - m_fadeRate);
	}
}

void SceneManager::CheckFileLoadingStart()
{
	auto num = GetASyncLoadNum();
	// 非同期ロードしているものがあったらFileLoadingに変更
	if (num > 0)
	{
		// 非同期ロードの開始
		m_updateFunc = &SceneManager::FileLoadingUpdate;
		m_drawFunc = &SceneManager::FileLoadingDraw;
	}
}

