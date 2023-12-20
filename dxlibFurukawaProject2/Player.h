#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;

class Player
{
public:
	// 向いている方向
	enum Dir
	{
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp		// 上
	};

public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw() const;

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	// プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() { return m_colRect; }
	
	void OnDamage();

private:
	SceneMain* m_pMain;

	int m_handle;	// グラフィックのハンドル

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;

	// 向いている方向
	Dir m_dir;
	// 歩きアニメーション
	int m_walkAnimFrame;

	// 魔法の杖の発射フレーム
	int m_magicWandFrame;

	// ダメージを受けてからのフレーム数
	// 普段は0
	// 当たった時にフレーム数を設定して
	// 以降毎フレーム減らしていく
	int m_damageFrame;
};

