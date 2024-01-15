#pragma once
#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class RankingScene
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン更新用
	int _countFrame;//タイマ用
public:
	/*コンストラクタ*/
	RankingScene() :
		_nextScene(SceneKind::GAMESCENE),
		_countFrame(0)
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
		DrawString(600, 480, "RankingScene", GetColor(255, 255, 255));
	}

};