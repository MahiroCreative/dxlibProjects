#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "ShootingPlayer.h"

class SceneShooting : public _baseGameScene
{
public:
	/*コンストラクタデストラクタ*/ 
	//コンストラクタ
	SceneShooting()
		: _nextScene()
	{
		Init();
	}
	//デストラクタ
	~SceneShooting() = default;

	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//更新
	int Update() override;
	//描画
	void Draw() override;

	/*メンバ関数*/
	//任意のキーでタイトルに戻る
	void CheckReturnTitle(int KeyCode);
private:
	/*処理変数*/
	//nextScene.
	GameSetting::SceneState _nextScene;

	/*ゲームオブジェクト変数*/
	std::unique_ptr<ShootingPlayer> _player;
};