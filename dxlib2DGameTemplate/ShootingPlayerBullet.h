#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"

class ShootingPlayerBullet
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	ShootingPlayerBullet()
		: _transform(), _rigidbody(), _color()
	{
		Init();
	}
	//デストラクタ
	~ShootingPlayerBullet() = default;

	/*定型メンバ関数*/
	//初期化
	void Init();
	//初期化
	void Init(Vector2 playerPos);
	//更新
	void Update();
	//描画
	void Draw();

	/*メンバ関数*/
	//移動
	void Move();
	//画面外判定
	bool IsOutOfScreen();
private:
	/*処理変数*/
	//transform.
	Transform2D _transform;
	//rigidbody.
	Rigidbody2D _rigidbody;
	//speed.
	float _moveSpeed = 6.0f;
	//color.
	unsigned int _color;
};

