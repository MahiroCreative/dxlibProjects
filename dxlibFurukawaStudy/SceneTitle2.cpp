#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "SceneTitle2.h"

SceneTitle::SceneTitle() :
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_decideSe(-1),
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneTitle::~SceneTitle()
{
}