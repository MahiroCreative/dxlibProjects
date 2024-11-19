#include "PauseScene.h"
#include <DxLib.h>
#include"Pad.h"
#include "Application.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include"TitleScene.h"
#include"Game.h"
#include"SoundManager.h"
#include"GraphManager.h"
#include"FontManager.h"
#include"Physics.h"


namespace
{
	constexpr int kAppeaInterval = 60;
	constexpr int kMenuMargin = 50;

	/// <summary>
	/// �ꕶ������OffsetX(������𒆐S���W���w�肵��Draw�������Ƃ��Ɏg���B���S���W-kCharPosOffSetX*�������Ǝg��)
	/// </summary>
	constexpr int kCharPosOffSetX = 4;
	/// <summary>
	/// �ꕶ������OffsetX
	/// </summary>
	constexpr int kCharPosOffSetY = 6;

	
	constexpr int kFadeFrameMax = 60;
	const char* kFrameName = "Frame.png";

}

PauseScene::PauseScene(SceneManager& mgr) : Scene(mgr),
m_soundVol(SoundManager::GetInstance().GetSoundVol()),
m_btnFrame(0),
m_fadeSpeed(1),
m_frameHandle(GraphManager::GetInstance().GetGraphData(kFrameName)),
m_fontHandle(FontManager::GetInstance().GetFontData("SF_font.ttf", "���z�� �l�N�X�g UP B", 60, 7, DX_FONTTYPE_NORMAL)),
m_tutoFlag(false)
{
	m_updateFunc = &PauseScene::AppearUpdate;
	m_drawFunc = &PauseScene::ExpandDraw;
	m_tutoHandle =GraphManager::GetInstance().GetGraphData("information.png");
	
}

void PauseScene::Load()
{
}

void PauseScene::Update()
{
	(this->*m_updateFunc)();
	if (Pad::IsPress(PAD_INPUT_Z))
	{
		m_soundVol++;
	}
	if (Pad::IsPress(PAD_INPUT_Y))//XBox�R���g���[���[��L
	{
		m_soundVol--;
	}

	SoundManager::GetInstance().ChangeSoundVolume(m_soundVol);

	m_btnFrame += m_fadeSpeed;
	if (m_btnFrame > kFadeFrameMax)m_fadeSpeed *= -1;
	if (m_btnFrame < 0)m_fadeSpeed *= -1;

	Pad::Update();
}

void PauseScene::Draw()
{
	(this->*m_drawFunc)();
}

void PauseScene::AppearUpdate()
{
	m_frame += 2;
	if (kAppeaInterval <= m_frame)
	{
		m_updateFunc = &PauseScene::NormalUpdate;
		m_drawFunc = &PauseScene::NormalDraw;
	}
}

void PauseScene::NormalUpdate()
{
	if (!m_tutoFlag)
	{
		if (Pad::IsTrigger(PAD_INPUT_R))
		{
			m_updateFunc = &PauseScene::DisappearUpdate;
			m_drawFunc = &PauseScene::ExpandDraw;

		}
		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_select++;
		}
		if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_select--;
		}
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		if (m_select % 3 == 0)
		{
			m_updateFunc = &PauseScene::DisappearUpdate;
			m_drawFunc = &PauseScene::ExpandDraw;
		}
		if(m_select % 3 == 1|| m_select % 3 == -2)
		{
			if (m_tutoFlag)
			{
				m_tutoFlag = false;
			}
			else if(!m_tutoFlag)
			{
				m_tutoFlag = true;
			}

		}
		if (m_select % 3 == 2 || m_select % 3 == -1)
		{
			m_manager.ResetScene(std::make_shared<TitleScene>(m_manager));
			MyEngine::Physics::GetInstance().Clear();
		}
	}

}

void PauseScene::DisappearUpdate()
{
	m_frame -= 2;
	if (m_frame == 0)
	{
		m_manager.PopScene();
	}
}

void PauseScene::ExpandDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	int halfHeight = (size.h - 100) / 2;
	int centerY = size.h / 2;

	float rate = static_cast<float>(m_frame) / kAppeaInterval;	// ���݂̎��Ԃ̊���(0.0�`1.0)
	int currentHalfHeight = static_cast<int>(rate * halfHeight);

	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	// ������ƈÂ���`��`��
	DrawBox(kMenuMargin, centerY - currentHalfHeight, size.w - kMenuMargin, centerY + currentHalfHeight,
		0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(kMenuMargin, centerY - currentHalfHeight, size.w - kMenuMargin, centerY + currentHalfHeight,
		0xffffff, false);
}

void PauseScene::NormalDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	// ������ƈÂ���`��`��
	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaString(670, 300, 6, 6, 0, 0, 0, 0xffffbb, 0, 0, "Pause");

	DrawExtendFormatStringToHandle(750, 500,0.3f,0.3f,  0xffffff,m_fontHandle,"�Q�[���ɖ߂�");
	DrawExtendFormatStringToHandle(770, 600, 0.3f, 0.3f, 0xffffff,m_fontHandle, "�������");
	DrawExtendFormatStringToHandle(760, 700, 0.3f, 0.3f, 0xffffff,m_fontHandle, "�^�C�g����");

	if (m_select % 3 == 0)
	{
		DrawRectExtendGraph(690 - static_cast<int>(m_btnFrame) / 6, 470 - static_cast<int>(m_btnFrame) / 6, 920 + static_cast<int>(m_btnFrame) / 6, 540 + static_cast<int>(m_btnFrame) / 6, 0, 0, 4167, 4167, m_frameHandle, true);
	}
	if (m_select % 3 == 1 || m_select % 3 == -2)
	{
		DrawRectExtendGraph(690 - static_cast<int>(m_btnFrame) / 6, 570 - static_cast<int>(m_btnFrame) / 6, 920 + static_cast<int>(m_btnFrame) / 6, 640 + static_cast<int>(m_btnFrame) / 6, 0, 0, 4167, 4167, m_frameHandle, true);
	}
	if (m_select % 3 == 2 || m_select % 3 == -1)
	{
		DrawRectExtendGraph(690 - static_cast<int>(m_btnFrame) / 6, 670 - static_cast<int>(m_btnFrame) / 6, 920 + static_cast<int>(m_btnFrame) / 6, 740 + static_cast<int>(m_btnFrame) / 6, 0, 0, 4167, 4167, m_frameHandle, true);
	}


	if (m_tutoFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
		// ������ƈÂ���`��`��
		DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
			0x111111, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 0.8f, 0, m_tutoHandle, true);
	}

	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0xffffff, false);

}
