#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"
#include "ShootingPlayer.h"
#include "ShootingEnemy.h"

// 型エイリアスを定義
using BulletPtr = std::unique_ptr<SimpleBullet>;
using BulletVector = std::vector<BulletPtr>;

class ShootingScene : public _baseGameScene
{
public:
	/*コンストラクタデストラクタ*/ 
	//コンストラクタ
	ShootingScene()
		: _nextScene()
	{
		Init();
	}
	//デストラクタ
	~ShootingScene() = default;

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
	//PlayreBulletの生成
	void CreatePlayerBullet();
	void UpdatePlayerBullet();
	void DeletePlayerBullet();
private:
	/*処理変数*/
	//nextScene.
	GameSetting::SceneState _nextScene;
	//PlayerBullet生成用のタイマー
	int _playerBulletTimer;

	/*ゲームオブジェクト変数*/
	std::unique_ptr<ShootingPlayer> _player;
	std::unique_ptr<ShootingEnemy> _enemy;
	// 単一のBulletオブジェクト変数
	BulletPtr _pPlayerBullet;
	// Bulletオブジェクト用のベクター
	BulletVector _vPlayerBullets;
};