#pragma once
#include "SceneBase.h"
#include "Player.h"

class SceneMain :
    public SceneBase
{
private:
    /*�����o�ϐ�*/
    Player m_player;
    /*�����o�֐�*/
    void Update() const override;
};

