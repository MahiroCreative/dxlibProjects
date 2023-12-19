#pragma once

// 1クラス1ファイルを心掛ける

// なぜわざわざクラスのメンバをprivateにするの？
// すべてpublicなら便利では？

// const	値をいじれないようにする
// 値をいじれた方が便利　→間違えていじることを防ぐためにconstでそもそもいじれないようにする

// ・クラスの処理はクラス自身にやらせる
// ・外から勝手に値をいじられないようにする
// 例．敵を非表示にしたい 勝手に画面外の座標に移動させる、みたいなことが発生する　→敵は生きているはずなのに画面に表示されない？といったバグ

class Enemy
{
public:
	// コンストラクタ、デストラクタは特殊な事をしない限りpublic
	Enemy();
	~Enemy();

	// クラス外で使いたい(今回はWinMainで使う)ものはpublic
	void Init();
	//	void Update();
	void Draw();

	// クラス外からメンバ変数を変更した場合はpublicなメンバ関数を通す
	void SetPos(int x, int y);

	// 簡単な中身ならヘッダに直接書くことも多い
	void SetPosX(int x) { m_posX = x; }
	void SetPosY(int y) { m_posX = y; }

private:
	// メンバ変数はすべてprivate
	int m_handle;
	int m_posX;
	int m_posY;
};
