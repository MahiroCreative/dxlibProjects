#include "ShootingPlayer.h"

/*定型メンバ関数*/
//初期化
void ShootingPlayer::Init()
{
	//初期化
	_transform.Position = Vector2(0, 0);//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_collision.Center = _transform.Position;//中心
	_collision.Radius = 12;//コリジョンの半径
	_collision.Color = Color::RedColor;//色
	_color = GetColor(255, 255, 255);//色
	_moveSpeed = 2.0f;//移動速度
	_shotInterval = 10;//ショットのインターバル
	_shotFrame = 0;//ショットフレーム
	_chargeShotInterval = 60;//チャージショットのインターバル
	_chargeFrame = 0;//チャージフレーム
	_isShot = false;//ショットフラグ
	_isChargeShot = false;//チャージショットフラグ
	_shotSize = 4;//ショットの大きさ
	_chargeShotSize = 20;//チャージショットの大きさ
	_shotSpeed = 8;//ショットの速度
	_chargeShotSpeed = 12;//チャージショットの速度
	_shotKey = KEY_INPUT_RETURN;//ショットキー
	_hp = 3;//HP

}
void ShootingPlayer::Init(Vector2 pos)
{
	//初期化
	Init();//初期化
	_transform.Position = pos;//位置
}
void ShootingPlayer::Init(Vector2 pos, float moveSpeed)
{
	//初期化
	Init();//初期化
	_transform.Position = pos;//位置
	_moveSpeed = moveSpeed;//移動速度
}

//更新
void ShootingPlayer::Update()
{
	//Key入力による速度の更新
	VelocityUpdate();

	//shotフラグの更新
	ShotFlagUpdate();

	//chargeShotフラグの更新
	ChargeShotFlagUpdate();

	//コリジョンの位置更新
	CollisionUpdate();

	//移動
	Move();
}

//描画
void ShootingPlayer::Draw()
{
	//プレイヤーの描画
	PlayerDraw();

	//Debug描画
	DebugDraw();
}

//移動
void ShootingPlayer::Move()
{
	//移動
	_transform.Position += _rigidbody.Velocity * _moveSpeed;

	//加速
	_rigidbody.Velocity += _rigidbody.Acceleration;

	//ストップ
	if (_transform.Position.X <= 0) { _rigidbody.Velocity.X = 0; }//左端
	if (_transform.Position.X >= GameSetting::WINDOW_WIDTH) { _rigidbody.Velocity.X = 0; }//右端
	if (_transform.Position.Y <= 0) { _rigidbody.Velocity.Y = 0; }//上端
	if (_transform.Position.Y <= 0) { _rigidbody.Velocity.Y = 0; }//下端
}

//速度の更新
void ShootingPlayer::VelocityUpdate()
{
	//Key入力チェック
	bool isUP = InputKey::isHoldKey(KEY_INPUT_W);
	bool isDOWN = InputKey::isHoldKey(KEY_INPUT_S);
	bool isLEFT = InputKey::isHoldKey(KEY_INPUT_A);
	bool isRIGHT = InputKey::isHoldKey(KEY_INPUT_D);

	//Key入力による速度の更新
	if (isUP) { _rigidbody.Velocity.Y = -1; }//上
	if (isDOWN) { _rigidbody.Velocity.Y = 1; }//下
	if (isLEFT) { _rigidbody.Velocity.X = -1; }//左
	if (isRIGHT) { _rigidbody.Velocity.X = 1; }//右

	//何も押されていない場合
	if (!isUP && !isDOWN && !isLEFT && !isRIGHT) { _rigidbody.Velocity = Vector2::Zero; }

	//速度の正規化
	if (_rigidbody.Velocity.LengthSq() > 0) { _rigidbody.Velocity = _rigidbody.Velocity.Normalize(); }

}

//Playerそのものの描画
void ShootingPlayer::PlayerDraw()
{
	//残像描画
	ShadowDraw();

	//Player描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), 10, _color, TRUE);

	//Effect描画
	EffectDraw();

}

//弾を撃つかどうか
void ShootingPlayer::ShadowDraw()
{
	//残像5
	DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 32), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 32), 1, GetColor(190, 190, 0), TRUE);
	//残像4
	DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 24), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 24), 2, GetColor(200, 200, 0), TRUE);
	//残像3
	DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 12), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 12), 4, GetColor(210, 210, 0), TRUE);
	//残像2
	DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 8), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 8), 6, GetColor(220, 220, 0), TRUE);
	//残像1
	DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 4), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 4), 8, GetColor(230, 230, 0), TRUE);
}

//チャージEffectの描画
void ShootingPlayer::EffectDraw()
{
	//チャージ演出
	if (_chargeFrame > 8)
	{
		//最大の大きさ制限
		int tempValue = _chargeFrame;
		if (tempValue > 100) { tempValue = 100; }
		//塵5
		DrawCircle(static_cast<int>(_transform.Position.X + _rigidbody.Velocity.X * 16), static_cast<int>(_transform.Position.Y + _rigidbody.Velocity.Y * 16), 0.04f * tempValue, GetColor(255, 5, 0), TRUE);
		//塵4
		DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 12), static_cast<int>(_transform.Position.Y + _rigidbody.Velocity.Y * 12), 0.08f * tempValue, GetColor(255, 45, 0), TRUE);
		//塵3
		DrawCircle(static_cast<int>(_transform.Position.X + _rigidbody.Velocity.X * 8), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 8), 0.12f * tempValue, GetColor(255, 85, 0), TRUE);
		//塵2
		DrawCircle(static_cast<int>(_transform.Position.X - _rigidbody.Velocity.X * 4), static_cast<int>(_transform.Position.Y - _rigidbody.Velocity.Y * 4), 0.16f * tempValue, GetColor(255, 125, 0), TRUE);
		//塵1
		DrawCircle(static_cast<int>(_transform.Position.X + _rigidbody.Velocity.X * 2), static_cast<int>(_transform.Position.Y + _rigidbody.Velocity.Y * 2), 0.20f * tempValue, GetColor(255, 165, 0), TRUE);
	}
}

void ShootingPlayer::ShotFlagUpdate()
{
	//ショット条件
	bool isShotFrame = (_shotFrame > _shotInterval);
	bool isDown = InputKey::isDownKey(_shotKey);

	//ショットフラグの更新
	if (isShotFrame && isDown)
	{
		_isShot = true;
		_shotFrame = 0;//ショットフレームのリセット
	}
	else
	{
		_isShot = false;
		_shotFrame++;//ショットフレームの更新
	}
}

void ShootingPlayer::ChargeShotFlagUpdate()
{
	//チャージショット条件
	bool isChargeFrame = (_chargeFrame > _chargeShotInterval);
	bool isNotHold = !InputKey::isHoldKey(_shotKey);

	//チャージショットフラグの更新
	if (isChargeFrame && isNotHold)
	{
		_isChargeShot = true;
		_chargeFrame = 0;//チャージフレームのリセット
	}
	else
	{
		_isChargeShot = false;
	}
	
	//チャージフレームの更新
	if(InputKey::isHoldKey(_shotKey))
	{
		_chargeFrame++;
	}
	else
	{
		_chargeFrame = 0;//チャージフレームのリセット
	}
}

void ShootingPlayer::CollisionUpdate()
{
	//コリジョンの中心位置更新
	_collision.Center = _transform.Position;
}

void ShootingPlayer::Damage()
{
	//HPを減らす
	_hp--;
}


/*Debug用*/
void ShootingPlayer::DebugDraw()
{
	//コリジョンの描画
	DrawCircle(static_cast<int>(_collision.Center.X), static_cast<int>(_collision.Center.Y), _collision.Radius, _collision.Color, FALSE);

	//Hpの描画
	DrawFormatString(0, 100, GetColor(255, 255, 255), "HP:%d", _hp);
}
