#include "InputKey.h"

void InputKey::Update()
{
	// 現在のキーの入力状態
	char tmpKey[256];
	// 全てのキーの入力状態を取得
	GetHitKeyStateAll(tmpKey);
	//全てのKeyの入力状態の確認
	for (int i = 0; i < 256; i++)
	{
		//i番のKeyが押されているかを判定
		if (tmpKey[i] != 0)
		{
			//押しているKeyのフレーム数加算
			KeyFrame[i]++;
		}
		else
		{
			//押されていないKeyのフレーム数初期化
			KeyFrame[i] = 0;
		}
	}
}

bool InputKey::isDownKey(int KeyCode)
{
	//Keyが押されている時間が1フレームの時
	if (KeyFrame[KeyCode] == 1)
	{
		return true;
	}
	return false;
}

bool InputKey::isHoldKey(int KeyCode)
{
	//Keyが押されている時間が1フレーム以上の時
	if (KeyFrame[KeyCode] >= 1)
	{
		return true;
	}
	return false;
}

int InputKey::HoldKeyTime(int KeyCode)
{
	//Keyが押されている時間を返す
	if (KeyFrame[KeyCode] >= 1)
	{
		return KeyFrame[KeyCode];
	}
	return 0;
}


//静的メンバ変数の実態作成
int InputKey::KeyFrame[256];