#include "SceneMain.h"
#include "SceneBase.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*コンストラクタ*/
SceneMain::SceneMain():
	m_player()
{

}

/*メンバ関数*/
//frame毎の計算処理
void SceneMain::Update() const
{
	//Player
}
//frame毎の描画処理
void SceneMain::Draw() const
{
	//Player
	DrawGraph();
	m_player->m_drawHandle;

}
//frame毎の音声処理
void SceneMain::Sound() const
{
	
}