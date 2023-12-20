#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player;

/// <summary>
/// プレイヤーの攻撃の基底クラス
/// </summary>
class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;

	bool IsExist() const { return m_isExist; }
	/// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	/// <summary>
	/// 弾をスタートさせる
	/// </summary>
	/// <param name="pos">発射位置</param>
	virtual void Start(Vec2 pos) = 0;

protected:
	// SceneMainの関数を呼び出すポインタを覚えておく
	SceneMain* m_pMain;
	// ショットを撃ったプレイヤーのポインタを覚えておく
	Player* m_pPlayer;

	bool m_isExist;	// 存在しているかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
};

