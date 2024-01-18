#pragma once
#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class RankingScene
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン遷移用
public:
	/*メンバ変数*/
	static int _maxScore;
	/*コンストラクタ*/
	RankingScene() :
		_nextScene(SceneKind::RANKING)
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
		DrawString(8, 8, "SceneName:RankingScene", GetColor(255, 255, 255));

		//スコアの表示
		DrawString(500, 500, "SceneName:RankingScene", GetColor(255, 255, 255));

	}
	/// <summary>
	/// インスタンスの初期化
	/// </summary>
	void Init()
	{
		//メンバ変数の初期化
		_nextScene = SceneKind::RANKING;
	}

};
int RankingScene::_maxScore = 0;