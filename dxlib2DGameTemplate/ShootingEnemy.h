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
		:_transform(), _rigidbody(), _color(), _moveSpeed(), _chargeFrame(0), _shotSize(4), _chargeShotSize(20), _shotSpeed(-8), _chargeShotSpeed(-12)
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

	/*ゲッター*/
	//transformのゲッター
	Transform2D GetTransform() { return _transform; }
	//shotSpeedのゲッター
	int GetShotSpeed() { return _shotSpeed; }
	//shotSizeのゲッター
	int GetShotSize() { return _shotSize; }
	//shotのフラグ
	bool IsShot() { return _isShot; }


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
	//ChargeFrame(チャージ時間)
	int _chargeFrame = 0;
	//shotのフラグ
	bool _isShot = false;
	//ChargeShotのフラグ
	bool _isChargeShot = false;
	//shotの大きさ
	int _shotSize = 4;
	//chaegeShotの大きさ
	int _chargeShotSize = 20;
	//shotSpeed.
	int _shotSpeed = -8;
	//chaegeShotSpeed.
	int _chargeShotSpeed = -12;
};

