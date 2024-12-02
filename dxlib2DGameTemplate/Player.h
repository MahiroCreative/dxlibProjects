#pragma once
#include "MyDxlib/MyDxlib.h"

class Player : public _baseGameObject2D
{
public:
	/*メンバ関数*/
	Player();
	~Player() override;
	//初期化
	void Init() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody _rigidbody;
};

void Player::Init()
{
	//初期化
	_transform.Position = Vector2(100, 100);
	_transform.Scale = Vector2(1.0f, 1.0f);
	_transform.Rotation = 0.0f;
	_rigidbody.Velocity = Vector2(0, 0);
	_rigidbody.Acceleration = Vector2(0, 0);
}

