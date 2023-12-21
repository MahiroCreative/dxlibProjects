#pragma once
#include "SceneBase.h"

/*プロタイプ宣言*/
class Player;

class SceneMain :
    public SceneBase
{
public:
    /*コンストラクタ*/
    SceneMain();
private:
    /*メンバ変数*/
    Player* m_player;
    /*メンバ関数*/
    //frame毎の計算処理
    void Update() const override;
    //frame毎の描画処理
    void Draw() const override;
    //frame毎の音声処理
    void Sound() const override;
};

