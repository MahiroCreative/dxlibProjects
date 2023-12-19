#include "SquareSceneMain.h"
#include <DxLib.h>
#include "SquareSceneMain.h"

namespace
{
	const unsigned int kWhiteColor = GetColor(255, 255, 255);
	const unsigned int kRedColor = GetColor(255, 0, 0);
}

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player.Init();
	m_player.SetFill(true);		// プレイヤーの矩形は塗りつぶす
	m_player.SetMouseTrase(true);	// プレイヤーの矩形はマウスに追従

	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Init();	// rectの初期化

		m_rect[i].SetRandom();
	}
}

void SceneMain::Update()
{
	m_player.Update();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Update();	// rectの毎フレームの更新処理
		// 移動後の情報を見て当たり判定を取る
		if (m_player.IsCollision(m_rect[i]))
		{
			// 当たっている場合の処理
			m_rect[i].SetColor(kRedColor);
		}
		else
		{
			// 当たっていない場合の処理
			m_rect[i].SetColor(kWhiteColor);
		}
	}
}

void SceneMain::Draw()
{
	m_player.Draw();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Draw();	// rectの描画
	}
}

void SceneMain::End()
{
}