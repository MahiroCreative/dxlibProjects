#include "ShootingEnemy.h"

void ShootingEnemy::Init()
{
	//初期化
	_transform.Position = Vector2(0, 0);
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 1);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_collision.Center = _transform.Position;//中心
	_collision.Radius = 80;//半径
	_collision.Color = Color::RedColor;//色
	_color = Color::CyanColor;//色
	_moveSpeed = 2.0f;//移動速度
	_chargeFrame = 0;//チャージフレーム
	_shotSize = 4;//ショットの大きさ
	_chargeShotSize = 40;//チャージショットの大きさ
	_shotSpeed = -8;//ショットの速度
	_chargeShotSpeed = -12;//チャージショットの速度
	_hp = 80;//HP
	_damageInterval = 20;//ダメージ後の無敵時間
	_damageFrame = 0;//ダメージを受けてからの時間
}

void ShootingEnemy::Init(Vector2 pos)
{
	//初期化
	Init();
	//代入
	_transform.Position = pos;
}

void ShootingEnemy::Update()
{
	//移動
	Move();
	//ショットフラグの更新
	ShotFlagUpdate();
	//チャージショットフラグの更新
	ChargeShotFlagUpdate();
	//コリジョンの更新
	CollisionUpdate();
	//無敵時間の更新
	DamageUpdate();
}

void ShootingEnemy::Draw()
{
	//Enemy描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), 80, _color, TRUE);
	//Debug表示
	DebugDraw();
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

void ShootingEnemy::ShotFlagUpdate()
{
	//ランダムにショット
	bool isRandShot = (rand() % 1000) < 8;

	//ショットフラグの更新
	if (isRandShot)
	{
		_isShot = true;
	}
	else
	{
		_isShot = false;
	}
}

void ShootingEnemy::ChargeShotFlagUpdate()
{
	//ランダムにチャージショット
	bool isRandChargeShot = (rand() % 1000) < 1;

	//チャージショットフラグの更新
	if (isRandChargeShot)
	{
		_isChargeShot = true;
	}
	else
	{
		_isChargeShot = false;
	}
}

void ShootingEnemy::CollisionUpdate()
{
	//コリジョンの中心位置更新
	_collision.Center = _transform.Position;
}

void ShootingEnemy::Damage(int damage)
{
	//ダメージ条件
	bool isDamage = (_damageFrame > _damageInterval);

	//ダメージを受ける
	if (isDamage)
	{
		//Hpを減らす
		_hp = _hp - damage;
		//damageFrameのリセット
		_damageFrame = 0;
	}
}

void ShootingEnemy::DamageUpdate()
{
	//無敵時間の更新
	_damageFrame++;
	//上昇しすぎたら戻す
	if (_damageFrame > 80) { _damageFrame = 80; }
}

void ShootingEnemy::DebugDraw()
{
	//Hpの描画
	DrawFormatString(0, 48, GetColor(255, 255, 255), "EnemyHP:%d", _hp);
	//コリジョンの描画
	DrawCircle(static_cast<int>(_collision.Center.X), static_cast<int>(_collision.Center.Y), _collision.Radius, _collision.Color, FALSE);
}
