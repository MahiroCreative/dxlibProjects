#pragma once


class _baseGameObject2D
{
public:
	//メンバ関数
	virtual ~_baseGameObject2D() =0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};