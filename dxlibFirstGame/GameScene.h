#pragma once
#include "SceneBase.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

class GameScene : public SceneBase
{
public:
	/*コンストラクタ*/
	GameScene()
	{
		/*メンバ初期化*/
		p_player = new Player();
	}
	/*メンバ関数*/
	//frame毎の計算処理
	void Update() const override
	{
		//Player
		p_player->Update();
	}
	//frame毎の描画処理
	void Draw() const override
	{
		//Player
		p_player->Draw();
	}
	//frame毎の音声処理
	void Sound() const override
	{
		p_player->Sound();
	}
private:
	/*メンバ変数*/
	Player* p_player;
};

