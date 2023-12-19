#pragma once
// あまりヘッダーファイルでヘッダーファイルを
// インクルードするのは望ましくない
//#include "Player.h"

// クラスのプロトタイプ宣言
class Player;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw() const;	// 関数にconstをつけることでその関数の内部で
	// メンバー変数を変更できなくなる

private:
	// たくさん表示する用の定数
	// static constexpr int kPlayerNum = 65536 * 8;

private:

	int m_frameCount;

	Player* m_pPlayer;
};