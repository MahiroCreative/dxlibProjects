#include "ShootingPlayer.h"

void ShootingPlayer::Init()
{
	//初期化
	_transform.Position = Vector2(0, 0);//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
}

void ShootingPlayer::Init(Vector2 pos)
{
	//初期化
	_transform.Position = pos;//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
}

void ShootingPlayer::Update()
{
	//Key入力による速度の更新
	VelocityUpdate();

	//移動
	Move();
}

void ShootingPlayer::Draw()
{
	//描画
	DrawCircle(_transform.Position.X, _transform.Position.Y, 10, GetColor(255, 255, 255), TRUE);
}

void ShootingPlayer::Move()
{
	//移動
	_transform.Position += _rigidbody.Velocity * _moveSpeed;

	//加速
	_rigidbody.Velocity += _rigidbody.Acceleration;

	//ストップ
	if (_transform.Position.X <= 0) { _rigidbody.Velocity.X=0; }//左端
	if (_transform.Position.X >= GameSetting::WINDOW_WIDTH) { _rigidbody.Velocity.X = 0; }//右端
	if (_transform.Position.Y <= 0) { _rigidbody.Velocity.Y = 0; }//上端
	if (_transform.Position.Y <= 0) { _rigidbody.Velocity.Y = 0; }//下端
}

void ShootingPlayer::VelocityUpdate()
{
	//Key入力チェック
	bool isUP = InputKey::isHoldKey(KEY_INPUT_W);
	bool isDOWN = InputKey::isHoldKey(KEY_INPUT_S);
	bool isLEFT = InputKey::isHoldKey(KEY_INPUT_A);
	bool isRIGHT = InputKey::isHoldKey(KEY_INPUT_D);

	//Key入力による速度の更新
	if(isUP) { _rigidbody.Velocity.Y = -1; }//上
	if(isDOWN) { _rigidbody.Velocity.Y = 1; }//下
	if(isLEFT) { _rigidbody.Velocity.X = -1; }//左
	if(isRIGHT) { _rigidbody.Velocity.X = 1; }//右

	//何も押されていない場合
	if (!isUP && !isDOWN && !isLEFT && !isRIGHT) { _rigidbody.Velocity = Vector2::Zero; }

	//速度の正規化
	if(_rigidbody.Velocity.LengthSq() > 0){ _rigidbody.Velocity = _rigidbody.Velocity.Normalize(); }
	
}