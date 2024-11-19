#include "SceneManager.h"
#include "Scene.h"

namespace NextScene
{

}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	// �����̂ݎ��s
	m_scenes.back()->Update();
}

void SceneManager::Draw()
{
	// �擪���珇�ɕ`��(�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���)
	for (auto& scene : m_scenes)
	{
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (m_scenes.empty()) {	// ���X�g������ۂ����������ւ���̂ł͂Ȃ�
		m_scenes.push_back(nextScene);	// �����ɒǉ�����
	}
	else {
		m_scenes.back() = nextScene;	// ���łɈ�ȏ゠�����疖���̂��̂����ւ���
	}
}

void SceneManager::InsertScene(std::shared_ptr<Scene> nextScene)
{
	int b = 0;
	m_scenes.insert(m_scenes.begin(), nextScene);
}



void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	m_scenes.push_back(scene);
}

void SceneManager::PopScene()
{
	m_scenes.pop_back();
}

void SceneManager::ResetScene(std::shared_ptr<Scene> scene)
{
	m_scenes.clear();
	m_scenes.push_back(scene);
}

std::shared_ptr<Scene> SceneManager::LookBack()
{
	return m_scenes.back();
}
