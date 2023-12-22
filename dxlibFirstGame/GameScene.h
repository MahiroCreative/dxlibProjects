#pragma once
#include "SceneBase.h"

/*�v���^�C�v�錾*/
class Player;

class GameScene :
    public SceneBase
{
public:
    /*�R���X�g���N�^*/
    GameScene();
    /*�����o�֐�*/
    //frame���̌v�Z����
    void Update() const override;
    //frame���̕`�揈��
    void Draw() const override;
    //frame���̉�������
    void Sound() const override;
private:
    /*�����o�ϐ�*/
    Player* p_player;

};

