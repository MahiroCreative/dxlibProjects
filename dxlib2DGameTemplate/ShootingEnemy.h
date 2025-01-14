#pragma once
//STL.
#include <memory>
#include <vector>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "ShootingPlayerBullet.h"

class ShootingEnemy :public _baseGameObject2D
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	ShootingEnemy()
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

private:
	/*メンバ変数*/
	Transform2D _transform;
	Rigidbody2D _rigidbody;
};

