#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"

class SimpleBullet : public _baseGameObject2D
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	SimpleBullet() :
		_transform(),
		_rigidbody(),
		_collision(),
		_moveSpeed(),
		_color(),
		_size(),
		_tag("")
	{
		Init();
	}
	//デストラクタ
	~SimpleBullet() = default;

	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//初期化(オーバーロード)
	void Init(Vector2 pos);
	//初期化(オーバーロード)
	void Init(Vector2 pos, float moveSpeed);
	//初期化(オーバーロード)
	void Init(Vector2 pos, float moveSpeed, int size);
	//初期化(オーバーロード)
	void Init(Vector2 pos, float moveSpeed, int size, std::string tag);
	//初期化(オーバーロード)_colorはGetolorで取得
	void Init(Vector2 pos, float moveSpeed, int size, std::string tag, unsigned int color);
	//更新
	void Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	void Move();
	void CollisionUpdate();
	bool IsOutOfScreen();

	//getter.
	Transform2D GetTransform() { return _transform; }
	CircleCollision2D GetCollision() { return _collision; };
	std::string GetTag() { return _tag; }

private:
	/*メンバ変数*/
	//位置・倍率・回転
	Transform2D _transform;
	//速度
	Rigidbody2D _rigidbody;
	//Collision
	CircleCollision2D _collision;
	//移動速度
	float _moveSpeed;
	//色
	unsigned int _color;
	//サイズ
	int _size;
	//tag.
	std::string _tag;
};