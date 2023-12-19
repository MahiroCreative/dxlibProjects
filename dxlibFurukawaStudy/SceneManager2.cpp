#include <cassert>
#include "SceneManager2.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_title(),		// クラスの初期化時は()の中にコンストラクタの引数を書く
	m_main(),		// 今回はどのシーンもコンストラクタは引数を要求しないので
	m_result()		// m_title()のような書き方でOK
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// 初期化処理
	// 実行したいシーンの初期化を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Init();
		break;
	case kSceneKindMain:
		m_main.Init();
		break;
	case kSceneKindResult:
		m_result.Init();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::Update()
{
	// 前のフレームの時点で処理が終わっていたらシーンの切り替え
	// シーンの切り替えを行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		if (m_title.IsSceneEnd())
		{
			m_title.End();		// 実行していたシーンの終了処理

			// ゲームシーンへ遷移
			m_runScene = kSceneKindMain;	// 次のフレーム以降、実行したいシーン
			m_main.Init();		// 変更先のシーンの初期化
		}
		break;
	case kSceneKindMain:
		// 終了していたらSceneResultに切り替える
		if (m_main.IsSceneEnd())
		{
			// シーンを切り替える
			m_main.End();		// 実行していたシーンの終了処理

			m_runScene = kSceneKindResult;	// 次のフレーム以降、実行したいシーン
			m_result.Init();		// 変更先のシーンの初期化
		}
		break;
	case kSceneKindResult:
		if (m_result.IsSceneEnd())
		{
			m_result.End();		// 実行していたシーンの終了処理

			// タイトルへ遷移
			m_runScene = kSceneKindTitle;	// 次のフレーム以降、実行したいシーン
			m_title.Init();		// 変更先のシーンの初期化
		}
		break;
	default:
		assert(false);
		break;
	}

	// 実行中のシーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Update();
		break;
	case kSceneKindMain:
		m_main.Update();
		break;
	case kSceneKindResult:
		m_result.Update();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::Draw()
{
	// 実行中のシーンの描画を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Draw();
		break;
	case kSceneKindMain:
		m_main.Draw();
		break;
	case kSceneKindResult:
		m_result.Draw();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.End();
		break;
	case kSceneKindMain:
		m_main.End();
		break;
	case kSceneKindResult:
		m_result.End();
		break;
	default:
		assert(false);
		break;
	}
}