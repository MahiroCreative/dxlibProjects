#include "PlatformPlayer.h"

namespace
{
	constexpr int _kGravity = 1;
	constexpr int _kPlayerWidth = 24;
	constexpr int _kPlayerHeight = 32;
	constexpr float _kAcceleration = 0.5f;
	constexpr float _kFriction = 0.1f;
	const int _kPlayerColor = Color::YellowColor;
	const float _kMaxVelocity = 3;
	const float _kMaxGravity = 24;

}

void PlatformPlayer::Init()
{
	//変数初期化
	_transform.Position = Vector2(10, 100);//位置
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, _kGravity);//加速度
	_moveDir = Vector2(0, 0);//動く方向
	_state = PlayerState::Air;
}

void PlatformPlayer::Update()
{
	//ステートの更新
	UpdateState();
	//加速度の更新
	UpdateAcceleration();
	//速度の更新
	UpdateVelocity();
	//位置の更新
	UpdatePosition();
}

void PlatformPlayer::Draw()
{
	//描画位置の決定
	int PlayerPosX = _transform.Position.X;//X座標
	int PlayerPosY = _transform.Position.Y;//Y座標
	int DrawRightX = PlayerPosX + _kPlayerWidth;//右端のX座標
	int DrawRightY = PlayerPosY + _kPlayerHeight;//下端のY座標
	//描画
	DrawBox(PlayerPosX,PlayerPosY,DrawRightX,DrawRightY,_kPlayerColor,TRUE);
}

void PlatformPlayer::UpdateState()
{
	//条件出し
	bool isGround = _transform.Position.Y >= 600;

	//ステートの更新
	if (isGround) { _state = PlayerState::Ground; }//地面にいる
	else { _state = PlayerState::Air; }//空中にいる
}

void PlatformPlayer::UpdateAcceleration()
{
	//

	//重力加速度
	if (_state == PlayerState::Air) { _rigidbody.Acceleration.Y = _kGravity; };
}

void PlatformPlayer::UpdateVelocity()
{
	//速度の更新
	_rigidbody.Velocity += _rigidbody.Acceleration;

	//重力速度制限
	if (_rigidbody.Velocity.Y > _kMaxGravity) { _rigidbody.Velocity.Y = _kMaxVelocity; }
}

void PlatformPlayer::UpdatePosition()
{
	//位置の更新
	_transform.Position += _rigidbody.Velocity;
}
