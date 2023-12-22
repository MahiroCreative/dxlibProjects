#include "GameScene.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*コンストラクタ*/
GameScene::GameScene()
{
	/*メンバ初期化*/
	p_player = new Player();
}

/*メンバ関数*/
//frame毎の計算処理
void GameScene::Update() const
{
	//Player
	p_player->Update();
}
//frame毎の描画処理
void GameScene::Draw() const
{
	//Player
	p_player->Draw();

}
//frame毎の音声処理
void GameScene::Sound() const
{
	
}