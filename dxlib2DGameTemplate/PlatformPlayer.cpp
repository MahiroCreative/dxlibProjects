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

}

void PlatformPlayer::Init()
{
	//変数初期化
	_transform.Position = Vector2(10, 100);//位置
	_rigidbody.Velocity = Vector2(0, 0);//速度
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

void PlatformPlayer::UpdateAcceleration()
{
	//現在の加速度の取得
	Vector2 temp = _rigidbody.Acceleration;

	//KEY入力による加速度の更新
	if (InputKey::isHoldKey(KEY_INPUT_D)) { temp.X = _kAcceleration; }
	else if (InputKey::isHoldKey(KEY_INPUT_A)) { temp.X = -_kAcceleration; }
	else { temp.X = 0; }

	//重力による加速度の更新
	if (_transform.Position.Y <= 600) { temp.Y = _kGravity;}


	//加速度の更新
	_rigidbody.Acceleration = temp;

}

void PlatformPlayer::UpdateVelocity()
{
	//現在の速度の取得
	Vector2 temp = _rigidbody.Velocity;

	//加速度を加えて速度の更新
	temp += _rigidbody.Acceleration;

	//MAX速度を超えていないかの確認
	bool isOver = (temp.Length() > _kMaxVelocity);

	//MAX速度を超えていれば、速度をMAX速度にする
	if (isOver)
	{
		//速度の正規化
		//進みたい方向への大きさ1のベクトルを作成
		temp = temp.Normalize();
		//MAX速度を掛ける
		temp *= _kMaxVelocity;
		int i = 0;
	}

	//速度の更新
	_rigidbody.Velocity = temp;
}

void PlatformPlayer::UpdatePosition()
{
	//位置の更新
	_transform.Position += _rigidbody.Velocity;
}
