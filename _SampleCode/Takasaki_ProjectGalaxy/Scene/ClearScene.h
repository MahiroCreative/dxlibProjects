#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
public:
    ClearScene(SceneManager& mgr);
    ~ClearScene();

    void Load();
    void Update();
    void Draw();

private:

    int m_btnFrame = 0;
    int m_frame;
    int m_numFontHandle;
    int m_fontHandle;

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (ClearScene::*)();
    using DrawFunc_t = void (ClearScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // �X�V��Ԃ�\���֐�
    void FadeInUpdate();
    void NormalUpdate();
    void FadeOutUpdate();

    void ChangeScene(std::shared_ptr<Scene> nextScene);

    // �`���Ԃ�\���֐�
    void FadeDraw();
    void NormalDraw();

};

