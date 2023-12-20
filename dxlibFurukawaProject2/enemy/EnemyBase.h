#pragma once
#include "Vec2.h"
#include "Rect.h"

// 敵の基底クラス
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw() const;

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool IsExist() const { return m_isExist; }

	// 敵の座標を取得する
	Vec2 GetPos() const { return m_pos; };
	// 敵の当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// 敵キャラクターをスタートさせる
	virtual void Start() = 0;

protected:
	// m_posを左上にm_handleのグラフィックサイズを幅高さにした
	// 当たり判定を設定する
	virtual void UpdateCollision();

// private:	// 継承先から参照できない
protected:	// 継承先から参照できる
	int m_handle;	// グラフィックのハンドル

	bool m_isExist;	// 存在しているかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
};

