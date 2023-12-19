#include "DxLib.h"
#include "circlePlayer.h"
#include "circleEnemy.h"

namespace
{
	// �G�̐�
	constexpr int kEnemyNum = 3;
	// �G�̈ʒu���
	constexpr int kEnemyIntervalX = 160;
	//�F
	const unsigned int kRedColor = GetColor(255, 0, 0);
	const unsigned int kWhiteColor = GetColor(255, 255, 255);
}

void DispPlayerPos(Player& player)
{
	int x = player.GetPosX();
	int y = player.GetPosY();

	DrawFormatString(8, 460, GetColor(255, 255, 255), "(%3d, %3d)", x, y);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	player.Init();

	Enemy enemy[kEnemyNum];

	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i].Init();
	}

	int liveTime = GetNowCount();
	bool isFlag = true;

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		if (player.isExist())
		{
			// �Q�[���̏���
			player.Update();
			for (int i = 0; i < kEnemyNum; i++)
			{
				enemy[i].Update();
				player.Collision(enemy[i], kEnemyNum);
			}

			// �`��
			for (int i = 0; i < kEnemyNum; i++)
			{
				enemy[i].Draw();
			}
			player.Draw();

			DispPlayerPos(player);

			int time = (enemy[0].GetDelayChangTime() - (GetNowCount() - enemy[0].GetChangTime()));
			DrawFormatString(400, 0, kRedColor, "�X�s�[�h�ω��܂�%d.%d", time / 1000, time % 1000);
		}
		else
		{
			if (isFlag)
			{
				liveTime = GetNowCount() - liveTime;
				isFlag = false;
			}
			DrawFormatString(280, 220, kWhiteColor, "�����c���Ă������� %02d:%02d.%02d", liveTime / 60000, liveTime / 1000, liveTime % 1000);
			DrawString(280, 240, "R   �F���X�^�[�g", kWhiteColor);
			DrawString(280, 260, "ESC �F�I��", kWhiteColor);
			if (CheckHitKey(KEY_INPUT_R))
			{
				liveTime = GetNowCount();
				isFlag = true;
				player.Init();
				for (int i = 0; i < kEnemyNum; i++)
				{
					enemy[i].Init();
				}
			}
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		// 16.66ms(16667�}�C�N���b)�o�߂���܂ő҂�
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}