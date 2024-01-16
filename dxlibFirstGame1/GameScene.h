#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン更新用
	IntVector _charaPos;//キャラクタの位置
	int _charaHandle;
public:
	/*コンストラクタ*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_charaPos(240,240),
		_charaHandle(-1)
	{
		_charaHandle = LoadGraph("Chara.png");
	};
	/*メンバ関数*/
	//処理の更新
	SceneKind Update()
	{

		/*キャラ操作*/
		//up.
		if (MyKeyInput::isHoldKey(KEY_INPUT_UP))
		{
			_charaPos.Y -= 3;
		}
		//down.
		if (MyKeyInput::isHoldKey(KEY_INPUT_DOWN))
		{
			_charaPos.Y += 3;
		}
		//left.
		if (MyKeyInput::isHoldKey(KEY_INPUT_LEFT))
		{
			_charaPos.X -= 3;
		}
		//right.
		if (MyKeyInput::isHoldKey(KEY_INPUT_RIGHT))
		{
			_charaPos.X += 3;
		}


		/*シーン遷移処理*/
		//Enterキーを押したらTitleシーンに遷移
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}

		return _nextScene;
	}
	void Draw()
	{
		//現在のシーン名を描画
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));

		//キャラクターの描画
		DrawGraph(_charaPos.X,_charaPos.Y,_charaHandle,TRUE);
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