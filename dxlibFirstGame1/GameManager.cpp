#include <memory>
#include "DxLib.h"
#include "GameCommon.h"
#include "TitleScene.h"
#include "GameScene1.h"
#include "GameScene2.h"

//Dxlib�̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*�萔*/
	//��ʃT�C�Y
	constexpr int ScreenSizeX = 1280;//��
	constexpr int ScreenSizeY = 720;//����

	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	/*Dxlib������*/
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);//��ʃT�C�Y�Ɖ𑜓x
	ChangeWindowMode(true);//Window���[�h
	if (DxLib_Init() == -1) { return -1; }//Dxlib������
	SetDrawScreen(DX_SCREEN_BACK);//�_�u���o�b�t�@�����O

	/*Scene�̍쐬*/
	auto p_titleScene = std::make_unique<TitleScene>();
	auto p_gameScene1 = std::make_unique<GameScene1>();
	auto p_gameScene2 = std::make_unique<GameScene2>();

	/*�Q�[�����[�v��*/
	SceneKind nextScene = SceneKind::TITLESCENE;
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/
		if (nextScene == SceneKind::TITLESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_titleScene->Update();
			//�`�揈��
			p_titleScene->Draw();
		}
		else if (nextScene == SceneKind::GAMESCENE1)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_gameScene1->Update();
			//�`�揈��
			p_gameScene1->Draw();
		}
		else if (nextScene == SceneKind::GAMESCENE2)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_gameScene2->Update();
			//�`�揈��
			p_gameScene2->Draw();
		}
		else if(nextScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}


		//����ʂ�\��
		ScreenFlip();

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }

		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		//fps�Œ�(60fps:16.66ms)
		//���[�v�J�n��������16.66ms�o�܂Œ�~
		while (GetNowHiPerformanceCount() - roopStartTime < 16667) {}
	}

	/*�I������*/
	DxLib_End();//Dxlib�I������
	return 0;//�I�� 
}