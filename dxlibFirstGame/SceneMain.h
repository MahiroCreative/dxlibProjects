#pragma once
#include "SceneBase.h"
#include "Player.h"

class SceneMain :
    public SceneBase
{
private:
    /*ƒƒ“ƒo•Ï”*/
    Player m_player;
    /*ƒƒ“ƒoŠÖ”*/
    void Update() const override;
};

