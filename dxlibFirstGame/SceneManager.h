#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	/*メンバ変数*/
	//シーン処理用
	SceneBase* nowScene = nullptr;//現在のシーン
	//シーン確保用
	TitleScene* titleScene = nullptr;
	GameScene* gameScene = nullptr;
	//シーン更新用
	SceneBase::SceneKind  _nextScene;
public:
	/*コンストラクタ*/
	SceneManager()
	{
		//シーンの作成
		titleScene = new TitleScene();
		gameScene = new GameScene();
		//Input first.
		nowScene = titleScene;
		//nextScene.
		_nextScene = SceneBase::SceneKind::titleScene;
	}

	/*メンバ関数*/
	//処理の更新
	bool Update()
	{
		/*シーン計算処理*/
		_nextScene = nowScene->Update();

		/*シーン描画処理*/
		nowScene->Draw();

		/*シーン変更・終了処理*/
		switch (_nextScene)
		{
		case SceneBase::SceneKind::titleScene://titleScene.
			nowScene = titleScene;
			break;
		case SceneBase::SceneKind::gameScene://gameScene.
			nowScene = gameScene;
			break;
		case SceneBase::SceneKind::gameEnd://ゲーム終了
			//メモリ解放
			delete titleScene;
			delete gameScene;
			//return.
			return false;
		}

		/*正常終了*/
		return true;
	}
};

