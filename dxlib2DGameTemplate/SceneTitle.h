#pragma once
//STL.
#include <memory>
//origin.
#include "MyDxlib2DGame/MyDxlib2DGame.h"
#include "Player.h"

//タイトルシーンクラス
class SceneTitle : public _baseGameScene
{
public:
	/*メンバ関数*/
	//初期化
	void Init() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
private:
	/*ゲームオブジェクト*/
	//Arrow.シーン選択用の矢印。

};

