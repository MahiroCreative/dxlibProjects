#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneMapEdit.h"
#include "Pad.h"

SceneManager::SceneManager()
{
	// クラスのメモリを確保する
	m_pMain = new SceneMain;
	m_pMapEdit = new SceneMapEdit;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを解放する
	delete m_pMain;
	m_pMain = nullptr;

	delete m_pMapEdit;
	m_pMapEdit = nullptr;
}

void SceneManager::Init()
{
	m_pMain->Init();
}

void SceneManager::End()
{
	m_pMain->End();
}

void SceneManager::Update()
{
	Pad::Update();

	m_pMain->Update();
}

void SceneManager::Draw() const
{
	m_pMain->Draw();
}
