#include "SceneMain.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*コンストラクタ*/
SceneMain::SceneMain()
{
	/*メンバ初期化*/
	p_player = new Player();
}

/*メンバ関数*/
//frame毎の計算処理
void SceneMain::Update() const
{
	//Player
	p_player->Update();
}
//frame毎の描画処理
void SceneMain::Draw() const
{
	//Player
	p_player->Draw();

}
//frame毎の音声処理
void SceneMain::Sound() const
{
	
}