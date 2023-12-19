#include <DxLib.h>
#include <cassert>
#include "Game.h"
#include "SceneResult2.h"

SceneResult::SceneResult() :
	m_gameOverHandle(-1),
	m_bgHandle(-1),
	m_bgmHandle(-1),
	m_decideSe(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_lastPad(0),
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneResult::~SceneResult()
{
}