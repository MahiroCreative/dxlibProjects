#pragma once
#include "SceneBase.h"

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect();
	~SceneStageSelect() {}

	// シーンに入るときの初期化処理
	void Init() override;
	// 毎フレーム行う更新処理
	void Update(bool isFade) override;
	// 毎フレーム行う描画処理
	void Draw() const override;
	// シーンを抜けるときの処理
	void End() override;

private:
	void SelectUpdate();

private:
	int m_selectCurrent;

	int m_count;
};

