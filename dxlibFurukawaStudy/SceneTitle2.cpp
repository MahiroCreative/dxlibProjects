#include <DxLib.h>
#include <cassert>
#include "SceneTitle2.h"

// 定数定義
namespace
{
	// フェードの速度
	constexpr int kFadeSpeed = 8;

	// フェード後の待ち時間
	constexpr int kWaitFrame = 30;
}

SceneTitle::SceneTitle() :
	m_bgHandle{ -1, -1, -1, -1 },
	m_bgNo(0),
	m_fadeCount(0),
	m_fadeSpeed(0),
	m_waitFrame(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// フェードの初期化
	m_fadeCount = 255;			// 完全にフェードアウトしきった状態から
	m_fadeSpeed = -kFadeSpeed;	// フェードインさせる	-4:フェードイン 4:フェードアウト 0:待ち時間
	m_waitFrame = 0;

	// グラフィックのロード
	m_bgHandle[0] = LoadGraph("data/TitleBg000.jpg");
	assert(m_bgHandle[0] != -1);
	m_bgHandle[1] = LoadGraph("data/TitleBg001.jpg");
	assert(m_bgHandle[1] != -1);
	m_bgHandle[2] = LoadGraph("data/TitleBg002.jpg");
	assert(m_bgHandle[2] != -1);
	m_bgHandle[3] = LoadGraph("data/TitleBg003.jpg");
	assert(m_bgHandle[3] != -1);

	// 最初に表示する画像を指定する
	m_bgNo = 0;
}

void SceneTitle::Update()
{
	if (m_fadeSpeed == 0)
	{
		// 待ち時間
		m_waitFrame++;
		if (m_waitFrame >= kWaitFrame)
		{
			// フェードアウトに遷移
			m_fadeSpeed = kFadeSpeed;
		}
	}
	else if (m_fadeSpeed < 0)
	{
		// フェードイン中
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount <= 0)
		{
			m_fadeCount = 0;
			// 待ちに遷移
			m_fadeSpeed = 0;
			m_waitFrame = 0;	// 待ち時間初期化
		}
	}
	else	// m_fadeSpeed > 0
	{
		// フェードアウト中
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount >= 255)
		{
			// 画像を切り替えてフェードインに遷移する
			m_fadeCount = 255;
			// フェードインに遷移
			m_fadeSpeed = -kFadeSpeed;

			// 表示する画像を変更	0->1->2->3->0->1->...
			m_bgNo++;
			if (m_bgNo >= kBgNum)	m_bgNo = 0;
		}
	}
}

void SceneTitle::Draw()
{
	// 指定されている画像を表示する
	DrawGraph(0, 0, m_bgHandle[m_bgNo], false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);	// ここ以降、指定した透明度で描画する
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	// 元の設定(通常の不透明描画)に戻す
}

void SceneTitle::End()
{
	for (int i = 0; i < kBgNum; i++)
	{
		DeleteGraph(m_bgHandle[i]);
	}
}