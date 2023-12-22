#pragma once
#include "GameCommon.h"

class Player
{
public:
	/*コンストラクタ*/
	Player();
	/*メンバ関数*/
	void Update();
	void Draw();
	void Sound();
private:
	/*メンバ変数*/
	int _drawHandle;//画像ハンドル
	IntVector _pos;//座標
};

