#pragma once
#include "SceneBase.h"
#include "GameScene.h"
#include "TitleScene.h"

class SceneManager
{
private:
	/*メンバ変数*/
	//シーン更新用
	SceneBase* backScene = nullptr;//直前のシーン
	SceneBase* nowScene = nullptr;//現在のシーン
	SceneBase* nextScene = nullptr;//次のシーン
	//シーン確保用
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
public:
	/*コンストラクタ*/
	SceneManager()
	{
		//シーンの作成
		//gameScene = new GameScene();
		titleScene = new TitleScene();
		//Input first.
		nowScene = titleScene;
	}

	/*メンバ関数*/
	//処理の更新
	void Update()
	{
		nowScene->Update(nextScene);

		/*シーン変更*/
		if (nextScene != nullptr)
		{
			nowScene = nextScene;
			nextScene = nullptr;
		}
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

