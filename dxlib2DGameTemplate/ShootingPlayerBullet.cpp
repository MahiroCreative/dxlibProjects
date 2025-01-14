#include "ShootingPlayerBullet.h"

void ShootingPlayerBullet::Init()
{
	//初期化
	_transform.Position = Vector2(0.0f, 0.0f);
	_rigidbody.Velocity = Vector2::Right;
	_color = DxlibCommon::OrangeColor;
}

void ShootingPlayerBullet::Init(Vector2 playerPos)
{
	//初期化
	_transform.Position = playerPos;
	_rigidbody.Velocity = Vector2::Right;
	_color = DxlibCommon::OrangeColor;
}

void ShootingPlayerBullet::Update()
{
	//移動
	Move();
}

void ShootingPlayerBullet::Draw()
{
	//描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), 5, _color, TRUE);
}

void ShootingPlayerBullet::Move()
{
	//移動
	_transform.Position += _rigidbody.Velocity * _moveSpeed;

	//加速
	_rigidbody.Velocity += _rigidbody.Acceleration;
}

bool ShootingPlayerBullet::IsOutOfScreen()
{
	//画面外判定
	bool isOutLeft = _transform.Position.X <= 0;
	bool isOutRight = _transform.Position.X >= GameSetting::WINDOW_WIDTH;

	//画面外ならtrue
	if (isOutLeft || isOutRight) { return true; }

	//画面外でないならfalse
	return false;
}
