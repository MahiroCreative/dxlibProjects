#pragma once
#include "ShotBase.h"
class ShotBible : public ShotBase
{
public:
	ShotBible();
	virtual ~ShotBible();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() const override;

	/// <summary>
	/// 弾をスタートさせる
	/// </summary>
	/// <param name="pos">発射位置</param>
	virtual void Start(Vec2 pos) override;

private:
	// 一定時間経過したら消すために生成してからのフレームを数える
	int m_frameCount;

	// プレイヤーから見てどの方向にあるか
	float m_angle;
};

