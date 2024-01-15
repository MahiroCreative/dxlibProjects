#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene1
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン更新用
public:
	/*コンストラクタ*/
	GameScene1() :
		_nextScene(SceneKind::GAMESCENE1)
	{
	};
	/*メンバ関数*/
	//処理の更新
	SceneKind Update()
	{
		//Enterキーを押したら指定シーンに遷移
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::GAMESCENE2;
		}
		return _nextScene;
	}
	void Draw()
	{
		//現在のシーン名を描画
		DrawString(600, 480, "gameScene1", GetColor(255, 255, 255));
	}
};