#pragma once
/// <summary>
/// シーン全てが継承する抽象クラス。
/// 共通処理以外は継承先でオーバーライドして実装。 
/// </summary>
class SceneBase
{
public:
	/*メンバ変数*/
	//レイヤー番号を確保(layer0が背景)
	int Layer = -1;

	/*コンストラクタ・デストラクタ*/
	SceneBase() {};//コンストラクタはvirtual付けない。
	virtual ~SceneBase() {};//小で親のデストラクタが呼ばれないように

	/*メンバ関数*/
	//frame毎の計算処理
	virtual void Update() const = 0;
	//frame毎の描画処理
	virtual void Draw() const = 0;
	//frame毎の音声処理
	virtual void Sound() const = 0;
};

