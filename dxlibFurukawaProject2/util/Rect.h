#pragma once
#include "Vec2.h"

/// <summary>
/// 矩形を管理するためのクラス
/// </summary>
class Rect
{
public:
	Rect();
	virtual ~Rect();

	// 描画
	void Draw(unsigned int color, bool isFill) const;

	/// <summary>
	/// 左上座標と幅, 高さを保存
	/// </summary>
	/// <param name="left">左の座標</param>
	/// <param name="top">上の座標</param>
	/// <param name="width">幅</param>
	/// <param name="height">高さ</param>
	void SetLT(float left, float top, float width, float height);
	
	/// <summary>
	/// 中心座標と幅, 高さを保存
	/// </summary>
	/// <param name="x">中心座標: x</param>
	/// <param name="y">中心座標: y</param>
	/// <param name="width">幅</param>
	/// <param name="height">高さ</param>
	void SetCenter(float x, float y, float width, float height);

	// 必要な情報を取得する
	float GetWidth() const;		// 矩形の幅
	float GetHeight() const;	// 矩形の高さ
	Vec2 GetCenter() const;		// 矩形の中心座標

	/// <summary>
	/// 矩形同士の当たり判定
	/// </summary>
	/// <param name="target">判定側</param>
	/// <returns>true : 当たった, false : 当たってない</returns>
	bool IsCollsion(const Rect& target);

private:
	float m_left;	// 左のX座標 (左上)
	float m_top;	// 上のY座標 (左上)
	float m_right;	// 右のY座標 (右下)
	float m_bottom;	// 下のY座標 (右下)
};

