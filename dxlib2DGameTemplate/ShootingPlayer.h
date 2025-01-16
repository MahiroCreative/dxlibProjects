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
		_color(),
		_moveSpeed(2.0f),
		_shotInterval(20),
		_shotFrame(0),
		_chargeShotInterval(80),
		_chargeFrame(0)
	{
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

	/*プロパティ*/
	//Getter.
	Transform2D GetTransform() { return _transform; }
	bool IsShot() { return _isShot; }
	bool IsChargeShot() { return _isChargeShot; }
private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody2D _rigidbody;
	//色
	unsigned int _color;
	//移動速度
	float _moveSpeed = 2.0f;
	//shotのインターバル
	int _shotInterval = 20;
	//shotのtimer(前回のショットから経過したFrame)
	int _shotFrame = 0;
	//Chargeショットが発射できる時間
	int _chargeShotInterval = 80;
	//ChargeFrame(チャージ時間)
	int _chargeFrame=0;
	//shotのフラグ
	bool _isShot = false;
	//ChargeShotのフラグ
	bool _isChargeShot = false;
};