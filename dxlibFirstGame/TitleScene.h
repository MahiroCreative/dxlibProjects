#pragma once
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
    /*�R���X�g���N�^*/
    TitleScene();
    /*�����o�֐�*/
    //frame���̌v�Z����
    void Update() const override;
    //frame���̕`�揈��
    void Draw() const override;
    //frame���̉�������
    void Sound() const override;
};

