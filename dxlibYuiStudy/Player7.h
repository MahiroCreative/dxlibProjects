#pragma once

class Shot;

struct Player
{
	int x;
	int y;
	int handle;
	bool isPrevshot;
	int w;
	int h;
};

void InitPlayer(Player& player);

void UpdatePlayer(Player& player, Shot shot[], int shotArrayNum);

void DrawPlayer(Player& player);