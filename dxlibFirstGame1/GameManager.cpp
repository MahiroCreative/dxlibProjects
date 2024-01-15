#include <memory>
#include "DxLib.h"
#include "GameCommon.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "RankingScene.h"

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
	auto p_gameScene = std::make_unique<GameScene>();
	auto p_rankingScene = std::make_unique<RankingScene>();

	/*�Q�[�����[�v��*/
	//Scene�ϐ�
	SceneKind nowScene = SceneKind::TITLESCENE;
	SceneKind nextScene = SceneKind::TITLESCENE;
	//gameRoop.
	while (gameRoop)
	{
		//���[�v�J�n�����̊m��
		roopStartTime = GetNowHiPerformanceCount();

		//����ʂ̏�����
		ClearDrawScreen();

		/*�Q�[��������*/
		if (nowScene == SceneKind::TITLESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_titleScene->Update();
			//�`�揈��
			p_titleScene->Draw();
		}
		else if (nowScene == SceneKind::GAMESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_gameScene->Update();
			//�`�揈��
			p_gameScene->Draw();
		}
		else if (nowScene == SceneKind::RANKING)
		{
			//���o�͏���
			MyKeyInput::Update();
			//�v�Z����
			nextScene = p_rankingScene->Update();
			//�`�揈��
			p_rankingScene->Draw();
		}
		else if (nowScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}

		/*Scene�ύX����������*/
		if (nextScene != nowScene)
		{
			//�V�[���؂�ւ�
			nowScene = nextScene;
			//���ꂼ��̃V�[���̏���������
			if (nowScene == SceneKind::TITLESCENE)
			{
				nowScene;
			}
			else if(nowScene == SceneKind::RANKING)
			{
				nowScene;
			}
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