#pragma once
#include "MyDxlib2DGame/MyDxlib2DGame.h"

class Player : public _baseGameObject2D
{
public:
	/*メンバ関数*/
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
	_transform.Position = Vector2(100, 100);//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(1, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
}

void Player::Update()
{
	//左右移動
	_transform.Position += _rigidbody.Velocity;

	//ストップ
	if (_transform.Position.X == 400) { _rigidbody.Velocity = Vector2::Zero; }
}

void Player::Draw()
{
	//描画
	DrawCircle(_transform.Position.X, _transform.Position.Y, 10, GetColor(255, 255, 255), TRUE);
}
