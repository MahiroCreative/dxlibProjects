#pragma once
#include "DxLib.h"

/*入出力系*/
/// <summary>
/// 【ユーザ定義:static】【依存:Dxlib】
/// Keybordのみ。
/// </summary>
class KeyInput
{
private:
	/*staticメンバ変数*/
	//それぞれのKeyの入力フレーム数
	static int KeyFrame[];//定義だけ行い実態はグローバルで生成。
public:
	/*staticメンバ関数*/
	/// <summary>
	/// Keyの入力状態の更新。
	/// 毎フレームごとに実行することで更新する。
	/// </summary>
	static void Update()
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
	/// <summary>
	/// Keyが押された瞬間を取得する。
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <param name="KeyCode">DxlibのKeyCode</param>
	static bool isDownKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] == 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Keyが押され続けているかを取得する。
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <param name="KeyCode">DxlibのKeyCode</param>
	static bool isHoldKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Keyが押されているフレーム数を取得する
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <returns>DxlibのKeyCode</returns>
	static int HoldKeyTime(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return KeyFrame[KeyCode];
		}
		return 0;
	}
};

//静的メンバ変数の実態作成
int MyKeyInput::KeyFrame[256];