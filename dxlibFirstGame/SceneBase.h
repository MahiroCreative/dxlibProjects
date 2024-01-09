#pragma once
#include "MyGameLib.h"

/// <summary>
/// シーン全てが継承する抽象クラス。
/// 共通処理以外は継承先でオーバーライドして実装。 
/// </summary>
class SceneBase
{
public:
	/*staticメンバ変数*/
	static enum SceneKind
	{
		gameEnd,
		titleScene
	};
	/*コンストラクタ・デストラクタ*/
	SceneBase() {};//コンストラクタはvirtual付けない。
	virtual ~SceneBase() {};//小で親のデストラクタが呼ばれないように

	/*メンバ関数*/
	//frame毎の計算処理
	virtual SceneKind Update() = 0;
	//frame毎の描画処理
	virtual void Draw() const = 0;
};

