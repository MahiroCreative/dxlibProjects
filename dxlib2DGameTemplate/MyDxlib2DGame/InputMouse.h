#pragma once
#include "DxLib.h"


/// <summary>
/// 【ユーザ定義:static】【依存:Dxlib】
/// マウス
/// </summary>
class MyMouseInput
{
private:
	/*staticメンバ変数*/
	//それぞれのMouseのFrame数
	static int MouseFrame[];//定義だけ行い実態は下で生成。
public:
	/*staticメンバ関数*/
	/// <summary>
	/// Mouseの入力状態の更新。
	/// 毎フレームごとに実行することで更新する。
	/// </summary>
	static void Update()
	{
		int tempMouse = GetMouseInput();

		//左クリック
		if (tempMouse == MOUSE_INPUT_LEFT)
		{
			//押されている
			MouseFrame[0]++;
		}
		else
		{
			//押されていない
			MouseFrame[0] = 0;
		}
		//右クリック
		if (tempMouse == MOUSE_INPUT_RIGHT)
		{
			//押されている
			MouseFrame[1]++;
		}
		else
		{
			//押されていない
			MouseFrame[1] = 0;
		}
	}
	/// <summary>
	/// Mouseが押された瞬間を取得する。	
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <param name="MouseCode">DxlibのMouseCode</param>
	static bool isDownKey(int MouseCode)
	{
		//左クリックの確認
		if ((MouseFrame[0] == 1) && (MOUSE_INPUT_LEFT == MouseCode))
		{
			return true;
		}
		//右クリックの確認
		if ((MouseFrame[1] == 1) && (MOUSE_INPUT_RIGHT == MouseCode))
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// マウスが押され続けているかを取得する。
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <param name="MouseCode"></param>
	/// <returns></returns>
	static bool isHoldKey(int MouseCode)
	{
		//左クリックの確認
		if ((MouseFrame[0] >= 1) && (MOUSE_INPUT_LEFT == MouseCode))
		{
			return true;
		}
		//右クリックの確認
		if ((MouseFrame[1] >= 1) && (MOUSE_INPUT_RIGHT == MouseCode))
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Keyが押されているフレーム数を取得する.
	/// Update()を毎フレーム行っている前提の関数。
	/// </summary>
	/// <param name="MouseCode"></param>
	/// <returns></returns>
	static int HoldKeyTime(int MouseCode)
	{
		//左クリックの確認
		if ((MouseFrame[0] >= 1) && (MOUSE_INPUT_LEFT == MouseCode))
		{
			return MouseFrame[0];
		}
		//右クリックの確認
		if ((MouseFrame[1] >= 1) && (MOUSE_INPUT_RIGHT == MouseCode))
		{
			return MouseFrame[1];
		}
		return 0;
	}
};
//静的メンバ変数の実態作成
int MyMouseInput::MouseFrame[2];