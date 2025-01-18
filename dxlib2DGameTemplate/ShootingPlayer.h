#pragma once
//STL.
#include <memory>
#include <vector>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "SimpleBullet.h"

// 型エイリアスを定義
using BulletPtr = std::unique_ptr<SimpleBullet>;
using BulletVector = std::vector<BulletPtr>;

class ShootingPlayer : public _baseGameObject2D
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	ShootingPlayer():
		_transform(),
		_rigidbody(),
		_collision(),
		_color(),
		_moveSpeed(),
		_shotInterval(),
		_shotFrame(0),
		_chargeShotInterval(),
		_chargeFrame(0),
		_isShot(false),
		_isChargeShot(false),
		_shotSize(),
		_chargeShotSize(),
		_shotSpeed(),
		_chargeShotSpeed(),
		_shotKey(),
		_hp(3),
		_damageInterval(0),
		_damageFrame(0)
	{
		//初期化
		Init();
	}
	//デストラクタ
	~ShootingPlayer() = default;

	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//初期化(オーバーロード)
	void Init(Vector2 pos);
	//初期化(オーバーロード)
	void Init(Vector2 pos, float moveSpeed);
	//更新
	void Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	//移動
	void Move();
	//速度の更新
	void VelocityUpdate();
	//Playerそのものの描画
	void PlayerDraw();
	//残像描画
	void ShadowDraw();
	//チャージEffectの描画
	void EffectDraw();
	//弾の発射フラグの更新
	void ShotFlagUpdate();
	//チャージショットの発射フラグの更新
	void ChargeShotFlagUpdate();
	//コリジョンの更新
	void CollisionUpdate();
	//Damage処理
	void Damage(int damage);
	//無敵時間の更新
	void DamageUpdate();

	/*プロパティ*/
	//Getter.
	Transform2D GetTransform() { return _transform; }
	CircleCollision2D GetCollision() { return _collision; }
	int GetShotSize() { return _shotSize; }
	int GetChargeShotSize() { return _chargeShotSize; }
	int GetShotSpeed() { return _shotSpeed; }
	int GetChargeShotSpeed() { return _chargeShotSpeed; }
	bool IsShot() { return _isShot; }
	bool IsChargeShot() { return _isChargeShot; }

	/*Debug用関数*/
	//コリジョン描画
	void DebugDraw();
private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody2D _rigidbody;
	//Collision
	CircleCollision2D _collision;
	//色
	unsigned int _color;
	//移動速度
	float _moveSpeed;
	//shotのインターバル
	int _shotInterval;
	//shotのtimer(前回のショットから経過したFrame)
	int _shotFrame;
	//Chargeショットが発射できる時間
	int _chargeShotInterval;
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
	//ShotKey.
	int _shotKey;
	//HP
	int _hp;
	//最大無敵時間(Frame)
	int _damageInterval;
	//ダメージを受けてからの時間
	int _damageFrame;
};