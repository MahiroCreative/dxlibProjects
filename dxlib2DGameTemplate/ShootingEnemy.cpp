#include "ShootingEnemy.h"

void ShootingEnemy::Init()
{
	//初期化
	_transform.Position = Vector2(0,0);
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 1);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_color = DxlibCommon::CyanColor;//色
	_moveSpeed = 2.0f;//移動速度
}

void ShootingEnemy::Init(Vector2 pos)
{
	//初期化
	_transform.Position = pos;
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 1);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_color = DxlibCommon::CyanColor;//色
	_moveSpeed = 2.0f;//移動速度
}

void ShootingEnemy::Update()
{
	//移動
	Move();
}

void ShootingEnemy::Draw()
{
	//Enemy描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), 80, _color, TRUE);
}

void ShootingEnemy::Move()
{
	//移動
	_transform.Position += _rigidbody.Velocity * _moveSpeed;
	//反転
	if (_transform.Position.Y < 80) { _rigidbody.Velocity = -_rigidbody.Velocity; }
	//反転
	if (_transform.Position.Y > GameSetting::WINDOW_HEIGHT - 80) { _rigidbody.Velocity = -_rigidbody.Velocity; }
}
