#include "SimpleBullet.h"

void SimpleBullet::Init()
{
	//初期化
	_transform.Position = Vector2(0.0f, 0.0f);
	_rigidbody.Velocity = Vector2::Right;
	_collision.Center = _transform.Position;//中心
	_collision.Radius = 10;//半径
	_collision.Color = Color::RedColor;//色
	_moveSpeed = 2.0f;
	_color = Color::OrangeColor;
	_size = 4;
	_tag = "";
}

void SimpleBullet::Init(Vector2 pos)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
	_moveSpeed = moveSpeed;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed, int size)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
	_moveSpeed = moveSpeed;
	_size = size;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed, int size, std::string tag)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
	_moveSpeed = moveSpeed;
	_size = size;
	_tag = tag;
}

void SimpleBullet::Init(Vector2 pos, float moveSpeed, int size, std::string tag, unsigned int color)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
	_moveSpeed = moveSpeed;
	_size = size;
	_tag = tag;
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
