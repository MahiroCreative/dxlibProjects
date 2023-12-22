#pragma once
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
    /*コンストラクタ*/
    TitleScene();
    /*メンバ関数*/
    //frame毎の計算処理
    void Update() const override;
    //frame毎の描画処理
    void Draw() const override;
    //frame毎の音声処理
    void Sound() const override;
};

