#include <DxLib.h>
#include <cassert>
#include "SceneMain2.h"
#include "Game.h"

namespace
{
	// “G‚Ì‰Šú¶¬ŠÔŠu(ƒtƒŒ[ƒ€”)
	constexpr int kEnemyWaitFrameDefault = 60;
	// “G‚ÌÅ’Z¶¬ŠÔŠu(ƒtƒŒ[ƒ€”)
	constexpr int kEnemyWaitFrameMin = 3;
	// “G‚Ì¶¬ŠÔŠu‚ğ“G‰½‘Ì¶¬‚·‚é‚½‚Ñ‚É’Z‚­‚·‚é‚©
	constexpr int kEnemyWaitFrameChangeNum = 5;
	// ˆê“x¶¬ŠÔŠu‚ğ’Z‚­‚·‚é‚Æ‚«‚É‰½ƒtƒŒ[ƒ€’Z‚­‚·‚é‚©
	constexpr int kEnemyWaitFrameChangeFrame = 1;

	// ƒQ[ƒ€ƒI[ƒo[‚É•\¦‚·‚é•¶š—ñ
	const char* const kGameOverString = "GameOver";
}

SceneMain::SceneMain()
//	m_playerHandle(-1),
//	m_enemyHandle(-1),
//	m_bgHandle(-1),
//	m_bgmHandle(-1),
//	m_enemyStartSe(-1),
//	m_hitSe(-1),
//	m_walkSe(-1),
//	m_player(),
//	m_enemy(),
//	m_isGameOver(false),
//	m_isSceneEnd(false),
//	m_playFrameCount(0),
//	m_enemyCreateNum(0),
//	m_enemyWaitFrame(0),
//	m_fadeAlpha(255)			// •s“§–¾‚Å‰Šú‰»
{
}

SceneMain::~SceneMain()
{
}