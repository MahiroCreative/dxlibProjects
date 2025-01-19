#pragma once
//STL.
#include <memory>
#include <vector>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "SimpleBullet.h"

class ShootingEnemy :public _baseGameObject2D
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	ShootingEnemy()
		:_transform(), _rigidbody(), _collision(),
		_color(), _moveSpeed(), _chargeFrame(0), _shotSize(), _chargeShotSize(), _shotSpeed(), _chargeShotSpeed(),
		_hp(), _damageInterval(), _damageFrame(0), _isShot(false), _isChargeShot(false), _timer(0), _timerInterval(0),
		_shotRate(0), _chargeShotRate(0)
	{
		Init();
	}
	//デストラクタ
	~ShootingEnemy() = default;
	
	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//初期化(オーバーロード)
	void Init(Vector2 pos);
	//更新
	void Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	//移動
	void Move();
	//shotのフラグの更新
	void ShotFlagUpdate();
	//chargeShotのフラグの更新
	void ChargeShotFlagUpdate();
	//Collisionの更新
	void CollisionUpdate();
	//Damage処理
	void Damage(int damage);
	//無敵時間の更新
	void DamageUpdate();
	//タイマの更新
	void TimerUpdate();

	/*ゲッター*/
	//transformのゲッター
	Transform2D GetTransform() { return _transform; }
	//Collisionのゲッター
	CircleCollision2D GetCollision() { return _collision; }
	//shotSpeedのゲッター
	int GetShotSpeed() { return _shotSpeed; }
	//shotSizeのゲッター
	int GetShotSize() { return _shotSize; }
	//chargeShotSizeのゲッター
	int GetChargeShotSize() { return _chargeShotSize; }
	//chargeShotSpeedのゲッター
	int GetChargeShotSpeed() { return _chargeShotSpeed; }
	//shotのフラグ
	bool IsShot() { return _isShot; }
	//chargeShotのフラグ
	bool IsChargeShot() { return _isChargeShot; }

	/*Debug用関数*/
	void DebugDraw();


private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody2D _rigidbody;
	//当たり判定
	CircleCollision2D _collision;
	//色
	unsigned int _color;
	//移動速度
	float _moveSpeed;
	//ChargeFrame(チャージ時間)
	int _chargeFrame;
	//shotのフラグ
	bool _isShot;
	//ChargeShotのフラグ
	bool _isChargeShot;
	//shotの大きさ
	int _shotSize;
	//chaegeShotの大きさ
	int _chargeShotSize;
	//shotSpeed.
	int _shotSpeed;
	//chaegeShotSpeed.
	int _chargeShotSpeed;
	//shotを撃つ確率
	int _shotRate;
	//chargeShotを撃つ確率
	int _chargeShotRate;
	//HP
	int _hp;
	//最大無敵時間(Frame)
	int _damageInterval;
	//ダメージを受けてからの時間
	int _damageFrame;
	//timer
	int _timer;
	//弾が大きくなり速度が上がるタイミング
	int _timerInterval;
};

