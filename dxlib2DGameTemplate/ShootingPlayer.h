#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "ShootingPlayerBullet.h"

class ShootingPlayer : public _baseGameObject2D
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	ShootingPlayer():
		_transform(),
		_rigidbody()
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
	//更新
	void Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	void Move();
	void VelocityUpdate();
private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody2D _rigidbody;
	//移動速度
	float _moveSpeed = 2.0f;
	//Bulletオブジェクト
	std::unique_ptr<ShootingPlayerBullet> _bullet;
};

