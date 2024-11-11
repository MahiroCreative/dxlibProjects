#pragma once
#include <sstream>
#include <iomanip>
#include "FontManager.h"

class TimeUtility
{
public:
	int min;
	int sec;
	int dec;

public:
	static TimeUtility FrameToTime(int frame)
	{
		TimeUtility time;
		// 分に変換
		time.min = frame / 3600;
		frame %= 3600;
		// 秒に変換
		time.sec = frame / 60;
		frame %= 60;
		// 少数以下に変換
		time.dec = static_cast<int>(frame / 60.0f * 100);
		return time;
	}
	static void DrawTime(int x, int y, unsigned int color, int fontSize, int frame)
	{
		const auto& time = FrameToTime(frame);

		std::wostringstream oss;
		oss << std::setfill(L'0') << std::setw(2) << time.min << L":";
		oss << std::setfill(L'0') << std::setw(2) << time.sec << L".";
		oss << std::setfill(L'0') << std::setw(2) << time.dec;

		DrawStringToHandle(x, y, oss.str().c_str(), color, FontManager::GetInstance().GetHandle(fontSize));
	}
};