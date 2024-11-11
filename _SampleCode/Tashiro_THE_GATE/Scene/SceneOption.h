#pragma once
#include "SceneBase.h"
#include <unordered_map>
#include <vector>
#include <memory>

class UIMoveData;

class SceneOption : public SceneBase
{
public:
	SceneOption();
	~SceneOption() {}

	// シーンに入るときの初期化処理
	void Init() override;
	// 毎フレーム行う更新処理
	void Update(bool isFade) override;
	// 毎フレーム行う描画処理
	void Draw() const override;
	// シーンを抜けるときの処理
	void End() override;

	void CheckOpenScene(SceneKind openScene);

private:
	void TitleUpdate();
	void MainUpdate();

	void SelectMainUpdate();
	void CheckMainUpdate();

	void DrawSoundBar(int y, int volume) const;

	void SoundChangeUpdate(int current);

private:
	using UpdateFunc_t = void(SceneOption::*)();
	UpdateFunc_t m_updateFunc;
	UpdateFunc_t m_mainUpdateFunc;

	std::unordered_map<SceneKind, std::vector<std::wstring>> m_selectStrList;

	std::vector<std::shared_ptr<UIMoveData>> m_uiList;
	std::shared_ptr<UIMoveData> m_soundUI;

	SceneKind m_openScene;

	int m_selectCurrent;
	int m_checkCurrent;

	bool m_isCheck;
};
