#pragma once
#include "circleEnemy.h"

class Player
{
public:
	Player();	// 作成時に呼ばれる
	~Player();	// 削除時に呼ばれる

	void Init();	// 初期化
	void Update();	// 毎フレームの更新処理
	void Draw() const;	// 描画
	void DrawPlayer() const;

	// 関数にconst
	// 関数内でメンバー変数の値を変更できなくなる
	int GetPosX() const { return m_posX; }		// 値の読み取り:X座標
	int GetPosY() const { return m_posY; }		// 値の読み取り:Y座標

	void Collision(Enemy& enemy, const int kEnemyNum);	// 当たり判定の確認

	bool isExist() const;

private:
	int m_posX;		// X座標
	int m_posY;		// Y座標
	int m_radius;	// 半径

	int m_hp;
	bool m_isHit;
};

void DrawHpBar(const int hp);