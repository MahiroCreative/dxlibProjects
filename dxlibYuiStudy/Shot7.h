#pragma once

class Enemy;

struct Shot
{
	int handle;
	int x;
	int y;
	bool isShot;
	int w;
	int h;
};

void InitShot(Shot& shot, int handle, int sizeW, int sizeH);

void UpdateShot(Shot& shot, Enemy& enemy);

void DrawShot(Shot& shot);