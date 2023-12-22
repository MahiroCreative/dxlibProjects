#pragma once
#include "SceneBase.h"
#include "GameScene.h"
#include "TitleScene.h"

class SceneManager
{
public:
	/*メンバ変数*/
	//シーン更新用
	SceneBase* backScene = nullptr;//直前のシーン
	SceneBase* nowScene = nullptr;//現在のシーン
	SceneBase* nextScene = nullptr;//次のシーン
	//シーン確保用
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;

	/*コンストラクタ*/
	SceneManager()
	{
		//シーンの作成
		gameScene = new GameScene();
		titleScene = new TitleScene();
		//Input first.
		nowScene = gameScene;
	}

	/*メンバ関数*/
	//処理の更新
	void Update()
	{
		nowScene->Update();
	}
	//描画の更新
	void Draw()
	{
		nowScene->Draw();
	}
	//音の更新
	void Soud()
	{
		nowScene->Sound();
	}
};

