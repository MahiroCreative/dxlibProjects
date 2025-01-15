#include "SimpleBullet.h"

void SimpleBullet::Init()
{
	//初期化
	_transform.Position = Vector2(0.0f, 0.0f);
	_rigidbody.Velocity = Vector2::Right;
	_moveSpeed = 2.0f;
	_color = DxlibCommon::OrangeColor;
	_size = 4;
}

void SimpleBullet::Init(Vector2 objectPos)
{
	//初期化
	_transform.Position = objectPos;
	_rigidbody.Velocity = Vector2::Right;
	_moveSpeed = 2.0f;
	_color = DxlibCommon::OrangeColor;
	_size = 4;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed)
{
	//初期化
	_transform.Position = pos;
	_rigidbody.Velocity = Vector2::Right;
	_moveSpeed = moveSpeed;
	_color = DxlibCommon::OrangeColor;
	_size = 4;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed, int size)
{
	//初期化
	_transform.Position = pos;
	_rigidbody.Velocity = Vector2::Right;
	_moveSpeed = moveSpeed;
	_size = size;
	_color = DxlibCommon::OrangeColor;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed, int size, unsigned int color)
{
	//初期化
	_transform.Position = pos;
	_rigidbody.Velocity = Vector2::Right;
	_moveSpeed = moveSpeed;
	_size = size;
	_color = color;
}

void SimpleBullet::Update()
{
	//移動
	Move();
}

void SimpleBullet::Draw()
{
	//描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), _size, _color, TRUE);
}

void SimpleBullet::Move()
{
	//移動
	_transform.Position += _rigidbody.Velocity * _moveSpeed;

	//加速
	_rigidbody.Velocity += _rigidbody.Acceleration;
}

bool SimpleBullet::IsOutOfScreen()
{
	//画面外判定
	bool isOutLeft = _transform.Position.X <= 0;
	bool isOutRight = _transform.Position.X >= GameSetting::WINDOW_WIDTH;

	//画面外ならtrue
	if (isOutLeft || isOutRight) { return true; }

	//画面外でないならfalse
	return false;
}
