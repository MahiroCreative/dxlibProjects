#pragma once
#include "SceneBase.h"
#include "TitleScene.h"

/*グローバル変数*/
enum SceneKind
{
	gameEnd,
	titleScene,
};

class SceneManager
{
private:
	/*メンバ変数*/
	//シーン処理用
	SceneBase* nowScene = nullptr;//現在のシーン
	//シーン確保用
	TitleScene* titleScene = nullptr;
	//シーン更新用
	SceneBase::SceneKind  _nextScene;
public:
	/*コンストラクタ*/
	SceneManager()
	{
		//シーンの作成
		titleScene = new TitleScene();
		//Input first.
		nowScene = titleScene;
	}

	/*メンバ関数*/
	//処理の更新
	bool Update()
	{
		/*シーン計算処理*/
		_nextScene = nowScene->Update();

		/*シーン描画処理*/
		nowScene->Draw();

		/*シーン変更処理*/

		/*ゲーム終了確認*/
		//作成中
		if (_nextScene == SceneKind::gameEnd){return false;}
		else{return true;}
	}
};

