#pragma once

#define ENEMY_NUM	5

typedef struct Enemy
{
	int handle;				// “Gî•ñ
	float x;				// Œ»İ‚ÌXÀ•W
	float y;				// Œ»İ‚ÌYÀ•W
	float moveX;			// X²‚ÌˆÚ“®‘¬“x
	float moveY;			// Y²‚ÌˆÚ“®‘¬“x
	float detectionLeft;	// “–‚½‚è”»’è¶‘¤
	float detectionRight;	// “–‚½‚è”»’è‰E‘¤
	float detectionUp;		// “–‚½‚è”»’èã‘¤
	float detectionDown;	// “–‚½‚è”»’è‰º‘¤
}Enemy;

// “G‚Ì‰Šú‰»
void initEnemy(Enemy* pEnemy, int tempHandle);

// ‘S‚Ä‚Ì“G‚Ì‰Šú‰»
void initAllEnmey(Enemy* pEnemy, int tempHandle);

// “G‚ÌˆÚ“®ŠÖ”
void updateEnemy(Enemy* pEnemy);

// ‘S‚Ä‚Ì“G‚ÌˆÚ“®ŠÖ”
void updateAllEnemy(Enemy* pEnemy);

// “G‚ğ•\¦‚·‚éŠÖ”
void drawEnemy(Enemy enemy);

// ‘S‚Ä‚Ì“G‚ğ•`‰æ‚·‚éŠÖ”
void drawAllEnemy(Enemy enemy[]);