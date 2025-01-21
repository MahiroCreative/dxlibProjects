#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "GameSetting.h"

class OverScene : public _baseGameScene
{
public:
	/*コンストラクタデストラクタ*/
	//コンストラクタ
	OverScene()
		: _nextScene(), _overText()
	{
		Init();
	}
	//デストラクタ
	~OverScene() = default;
	/*定型メンバ関数*/
	//初期化
	void Init() override;
	//更新
	int Update() override;
	//描画
	void Draw() override;
	/*メンバ関数*/
	//任意のキーでタイトルに戻る
	void CheckReturnTitle(int KeyCode);
private:
	/*メンバ変数*/
	//次のシーン
	GameSetting::SceneState _nextScene;
	//シーンロゴがわりの文字
	SimpleText _overText;
};