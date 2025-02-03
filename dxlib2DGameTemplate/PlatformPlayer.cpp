#include "PlatformPlayer.h"

namespace
{
	constexpr int _kGravity = 1;
	constexpr int _kPlayerWidth = 24;
	constexpr int _kPlayerHeight = 32;
	const int _kPlayerColor = Color::YellowColor;
	const float _kMaxVelocity = 4;
}

void PlatformPlayer::Init()
{
	//変数初期化
	_transform.Position = Vector2(10, 600);//位置
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
}

void PlatformPlayer::Update()
{
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

void PlatformPlayer::UpdateVelocity()
{
	//速度の取得
	Vector2 temp = _rigidbody.Velocity;

	//速度の制限


	//速度の更新
	_rigidbody.Velocity += _rigidbody.Acceleration;
}

void PlatformPlayer::UpdateAcceleration()
{
	//現在の加速度を確保
	Vector2 temp = _rigidbody.Acceleration;

	//Key入力による加速度の更新
	if (InputKey::isDownKey(KEY_INPUT_A)){ temp.X = -1;}
	if (InputKey::isDownKey(KEY_INPUT_D)) {temp.X = 1;}

	//加速度の更新
	_rigidbody.Acceleration = temp;
}

void PlatformPlayer::UpdatePosition()
{
	//位置の更新
	_transform.Position += _rigidbody.Velocity;
}
