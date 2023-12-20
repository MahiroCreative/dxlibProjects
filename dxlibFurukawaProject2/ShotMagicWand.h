#pragma once
#include "ShotBase.h"

#include "vector"

class ShotMagicWand : public ShotBase
{
public:
	ShotMagicWand();
	virtual ~ShotMagicWand();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() const override;

	/// <summary>
	/// 弾をスタートさせる
	/// </summary>
	/// <param name="pos">発射位置</param>
	virtual void Start(Vec2 pos) override;

private:
	// 残像を表示するために過去の位置を覚えておく
	std::vector<Vec2> m_posLog;
};
