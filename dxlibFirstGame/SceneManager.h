#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
//#include "GameScene.h"

/*シーン管理用*/
/// <summary>
/// シーン管理用の定数郡
/// </summary>
namespace SceneKind
{
	enum SceneName
	{
		ENDGAME,
		TITLESCENE,
		GAMESCENE,
	};
}

/*クラス定義*/
/// <summary>
/// シーン管理するマネージャークラス
/// </summary>
class SceneManager
{
private:
	/*メンバ変数*/
	//シーン処理用
	SceneBase* nowScene = nullptr;//現在のシーン
	//シーン確保用
	TitleScene* titleScene = nullptr;
	//GameScene* gameScene = nullptr;
public:
	/*staticメンバ変数*/
	//シーン更新用
	static SceneKind::SceneName s_nextScene;

	/*コンストラクタ*/
	SceneManager()
	{
		//シーンの作成
		titleScene = new TitleScene();
		//gameScene = new GameScene();
		//Input first.
		nowScene = titleScene;
		//nextScene.
		s_nextScene = SceneKind::TITLESCENE;
	}

	/*メンバ関数*/
	//処理の更新
	bool Update()
	{
		/*シーン計算処理*/
		s_nextScene = nowScene->Update();

		/*シーン描画処理*/
		nowScene->Draw();

		/*シーン変更・終了処理*/
		switch (s_nextScene)
		{
		case SceneKind::TITLESCENE://titleScene.
			nowScene = titleScene;
			break;
		case SceneKind::GAMESCENE://gameScene.
			//nowScene = gameScene;
			break;
		case SceneKind::ENDGAME://ゲーム終了
			//メモリ解放
			delete titleScene;
			//delete gameScene;
			//return.
			return false;
		}

		/*正常終了*/
		return true;
	}
};

