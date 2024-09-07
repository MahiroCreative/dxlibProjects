#pragma once
#include "DxLib.h"
#include "string"

using namespace std;

struct DebugString
{
	string value1;
	string value2;
	string value3;
	string value4;
	string value5;
	string value6;
	string value7;
	string value8;
	string value9;
	string value10;
	string value11;
	string value12;
};

void DebugDraw(DebugString* temp)
{
	//白色
	unsigned int Cr = GetColor(255, 255, 255);
	//sting型をcharに変換
	auto value1 = temp->value1.c_str();
	auto value2 = temp->value2.c_str();
	auto value3 = temp->value3.c_str();
	auto value4 = temp->value4.c_str();
	auto value5 = temp->value5.c_str();
	auto value6 = temp->value6.c_str();
	auto value7 = temp->value7.c_str();
	auto value8 = temp->value8.c_str();
	auto value9 = temp->value9.c_str();
	auto value10 = temp->value10.c_str();
	auto value11 = temp->value11.c_str();
	auto value12 = temp->value12.c_str();
	//表示
	DrawFormatString(0, 0, Cr, value1);
	DrawFormatString(0, 20, Cr, value2);
	DrawFormatString(0, 40, Cr, value3);
	DrawFormatString(0, 60, Cr, value4);
	DrawFormatString(0, 80, Cr, value5);
	DrawFormatString(0, 100, Cr, value6);
	DrawFormatString(0, 120, Cr, value7);
	DrawFormatString(0, 140, Cr, value8);
	DrawFormatString(0, 160, Cr, value9);
	DrawFormatString(0, 180, Cr, value10);
	DrawFormatString(0, 200, Cr, value11);
	DrawFormatString(0, 220, Cr, value12);
}