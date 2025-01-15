#include "ShootingPlayer.h"

void ShootingPlayer::Init()
{
	//初期化
	_transform.Position = Vector2(0, 0);//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_moveSpeed = 2.0f;//移動速度
}

void ShootingPlayer::Init(Vector2 pos)
{
	//初期化
	_transform.Position = pos;//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_moveSpeed = 2.0f;//移動速度
}

void ShootingPlayer::Init(Vector2 pos, float moveSpeed)
{
	//初期化
	_transform.Position = pos;//位置
	_transform.Scale = Vector2(1.0f, 1.0f);//倍率
	_transform.Rotation = 0.0f;//回転
	_rigidbody.Velocity = Vector2(0, 0);//速度
	_rigidbody.Acceleration = Vector2(0, 0);//加速度
	_moveSpeed = moveSpeed;//移動速度
}

void ShootingPlayer::Update()
{
	//Key入力による速度の更新
	VelocityUpdate();

	//Bulletの生成
	BulletCreate();

	//ChargeBulletの生成
	ChargeBulletCreate();

	//Bulletの更新
	BulletUpdate();

	//画面外に出た弾を削除
	BulletDelete();

	//移動
	Move();
}

void ShootingPlayer::Draw()
{
	//Bulletの描画
	BulletDraw();

	//プレイヤーの描画
	PlayerDraw();
}

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

void ShootingPlayer::PlayerDraw()
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
	//描画
	DrawCircle(static_cast<int>(_transform.Position.X), static_cast<int>(_transform.Position.Y), 10, GetColor(250, 250, 250), TRUE);
}

void ShootingPlayer::BulletCreate()
{
	//Bulletの生成
	if (InputKey::isDownKey(KEY_INPUT_RETURN) && _bulleTimer >= _bulletInterval)
	{
		//Bulletの生成
		_pBullet = std::make_unique<SimpleBullet>();
		//初期化
		_pBullet->Init(_transform.Position,8.0f);
		//Bulletの追加
		_vBullets.push_back(std::move(_pBullet));
		//Bulletの発射間隔のリセット
		_bulleTimer = 0;
	}

	//Bulletの発射timerの更新
	_bulleTimer++;
}

void ShootingPlayer::ChargeBulletCreate()
{
	//ChargeBulletの生成条件
	bool isCharge = (_chargeFrame >= 80);//30Frame以上押されているか
	bool isRelease = !(InputKey::isHoldKey(KEY_INPUT_RETURN));//リリースされたか

	//Chaege時間計測
	if (InputKey::isHoldKey(KEY_INPUT_RETURN)) { _chargeFrame++; }
	else { _chargeFrame = 0; }

	//ChargeBulletの生成
	if (isCharge && isRelease)
	{
		//ChargeBulletの生成
		_pBullet = std::make_unique<SimpleBullet>();
		_pBullet->Init(_transform.Position, 8.0f,20);
		//Bulletの追加
		_vBullets.push_back(std::move(_pBullet));
		//ChargeFrameのリセット
		_chargeFrame = 0;
	}
}

void ShootingPlayer::BulletUpdate()
{
	//Bulletの更新
	for (auto& bullet : _vBullets)
	{
		bullet->Update();
	}
}

void ShootingPlayer::BulletDraw()
{
	//Bulletの描画
	for (auto& bullet : _vBullets)
	{
		bullet->Draw();
	}
}

void ShootingPlayer::BulletDelete()
{
	// 弾の更新処理
	for (auto it = _vBullets.begin(); it != _vBullets.end();)
	{
		if ((*it)->IsOutOfScreen())
		{
			// 画面外に出た弾を削除
			//(削除した場合、空いた場所に後ろの要素が詰められる)
			it = _vBullets.erase(it); 
		}
		else
		{
			// 次の要素へ
			++it;
		}
	}
}
