#pragma once
//Scene.
#include "SceneBase.h"
#include "SceneManager.h"
//lib.
#include "MyGameLib.h"
#include "DxLib.h"
//gameObject.
#include "Player.h"


class GameScene : public SceneBase
{
private:
	/*メンバ変数*/
	Player* p_player;
	SceneBase::SceneKind _nextScene;
public:
	/*コンストラクタ*/
	GameScene()
	{
		/*メンバ初期化*/
		p_player = new Player();
		_nextScene = SceneBase::SceneKind::gameScene;
	}
	/*メンバ関数*/
	//frame毎の計算処理
	SceneBase::SceneKind Update() override
	{
		//Player
		p_player->Update();

		//debug.
		//if (CheckHitKey(KEY_INPUT_RETURN)) { return SceneKind::titleScene; }
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN)) { _nextScene = SceneKind::titleScene; }

		return _nextScene;
	}
	//frame毎の描画処理
	void Draw() const override
	{
		//Player
		p_player->Draw();
	}
};

