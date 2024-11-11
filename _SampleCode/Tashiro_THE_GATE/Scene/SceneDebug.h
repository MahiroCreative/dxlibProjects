#pragma once
#ifdef _DEBUG
#include "SceneBase.h"
class SceneDebug final : public SceneBase
{
public:
	SceneDebug();
	~SceneDebug() {}

	void Init() override;
	void Update(bool isFade) override;
	void Draw() const override;
	void End() override;

private:
	int m_next;
};
#endif
