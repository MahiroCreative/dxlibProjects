#pragma once
#include "Rect.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// クラスの定数定義
	// privateなのでこのクラス内でしか使えない
	static constexpr int kRectNum = 32;

private:
	Rect m_player;
	Rect m_rect[kRectNum];
};