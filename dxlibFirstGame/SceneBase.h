#pragma once
/// <summary>
/// シーン全てが継承する抽象クラス。
/// 共通処理以外は継承先でオーバーライドして実装。 
/// </summary>
class SceneBase
{
protected:
	/*メンバ変数*/
	//レイヤー番号を確保(layer0が背景)
	int m_layer=-1;
	/*メンバ関数*/
	//frame毎の計算処理
	virtual void Update();
	//frame毎の描画処理
	virtual void Draw();
	//frame毎の音声処理
	virtual void Sound();
};

