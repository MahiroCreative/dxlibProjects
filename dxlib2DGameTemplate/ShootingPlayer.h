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
		_pBullet(),
		_vBullets(),
		_bulleTimer(0),
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
	void Move();
	void VelocityUpdate();
	void PlayerDraw();
	void ChargeBulletCreate();
	void ShadowDraw();
	void EffectDraw();
	void BulletUpdate();
	void BulletDraw();
	void BulletDelete();
	Transform2D GetTransform() { return _transform; }
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
	// 単一のBulletオブジェクト変数
	BulletPtr _pBullet;
	// Bulletオブジェクト用のベクター
	BulletVector _vBullets;
	//Bulletの発射timer
	int _bulleTimer;
	//Bulletの発射間隔
	int _bulletInterval = 20;
	//ChargeFrame(チャージ時間)
	int _chargeFrame;
};