#pragma once

struct Enemy
{
	int x;
	int y;
	int handle;
	int damageHandle;
	int damageCounter;
	bool isDamage;
	int w;
	int h;
	bool isRightMove;
};

void InitEnemy(Enemy& enemy);

void UpdateEnemy(Enemy& enemy);

void DrawEnemy(Enemy& enemy);