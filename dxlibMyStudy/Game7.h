#pragma once


struct Position
{
	int x = 0;
	int y = 0;
};

struct Size
{
	int w = 0;
	int h = 0;
};

namespace
{
	constexpr int ScreenSizeX = 1280;
	constexpr int ScreenSizeY = 720;
	constexpr int ShotSpped = 8;
	constexpr int ShotNum = 20;
}