#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン更新用
public:
	/*コンストラクタ*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE)
	{
	};
	/*メンバ関数*/
	//処理の更新
	SceneKind Update()
	{
		//Enterキーを押したら指定シーンに遷移
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}
		return _nextScene;
	}
	void Draw()
	{
		//現在のシーン名を描画
		DrawString(600, 480, "gameScene", GetColor(255, 255, 255));
	}
	/// <summary>
	/// インスタンスの初期化
	/// </summary>
	void Init()
	{
		//メンバ変数の初期化
		_nextScene = SceneKind::GAMESCENE;
	}
};