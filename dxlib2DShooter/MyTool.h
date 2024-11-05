#pragma once
#include<iostream>
#include<string>
#include <time.h>
#include<chrono>
#include<ctime>

using namespace std;

/// <summary>
/// 現在時刻を表示
/// </summary>
/// <returns></returns>
void ShowNowTime()
{
	// 現在時刻をsystem_clockを用いて取得
	auto now = std::chrono::system_clock::now();

	// 現在時刻をtime_t形式に変換
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	//現在時刻を表示
	printf("%d", (t / 3600 + 9) % 24);//日
	printf(":%d", t / 60 % 60);//分
	printf(":%d", t % 60);//秒
}