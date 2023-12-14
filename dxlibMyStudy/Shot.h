#pragma once

// ショットの数.
#define SHOT 20

struct Enemy;

struct Shot
{
	//画像
	int handle = -1;
	//パラメータ
	Position pos;
	Size size;
	//フラグ
	bool isExist = false;
};

void InitializeShot(Shot& shot, int handle, int sizeW, int sizeH);// ショットの初期化処理
void UpdateShot(Shot& shot, Enemy& enemy);// 弾の更新処理
void DrawShot(Shot& shot);// 弾の描画処理