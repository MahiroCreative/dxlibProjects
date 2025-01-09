#pragma once
#include "MyDxlib/MyDxlib.h"

class Player : public _baseGameObject2D
{
public:
	/*メンバ関数*/
	//初期化
	void Init() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度・加速度
	Rigidbody _rigidbody;
};

