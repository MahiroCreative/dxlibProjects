#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"

enum PlayerState
{
	Ground,
	Air
};

class PlatformPlayer : public _baseGameObject2D
{
public:
	//コンストラクタとデストラクタ
	PlatformPlayer() : _transform(), _rigidbody(), _moveDir(), _state()
	{
		Init();
	}
	~PlatformPlayer() = default;

	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	//ステートの更新
	void UpdateState();
	//加速度の更新
	void UpdateAcceleration();
	//速度の更新
	void UpdateVelocity();
	//位置の更新
	void UpdatePosition();
private:
	//メンバ変数
	Transform2D _transform;
	Rigidbody2D _rigidbody;
	Vector2 _moveDir;//動く方向

	//State.
	PlayerState _state;
};

