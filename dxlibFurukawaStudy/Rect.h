#pragma once

class Rect
{
public:
	Rect();
	~Rect();

	void Init();
	void Update();
	void Draw() const;

	// 画面内のランダムな位置にランダムな大きさの矩形データを設定する
	void SetRandom();

	// ほかの矩形との当たり判定
	// 自身と指定したほかの矩形の当たり判定を取る
	bool IsCollision(const Rect& target) const;

	// publicな関数経由でメンバー変数変更
	void SetColor(unsigned int color) { m_color = color; }
	void SetFill(bool isFill) { m_isFill = isFill; }
	void SetMouseTrase(bool isTrase) { m_isMouseTrase = isTrase; }

	// 当たり判定実装用に上下左右の座標を取得できるようにする
	int GetLeft() const { return m_posX - m_width / 2; }
	int GetTop() const { return m_posY - m_height / 2; }
	int GetRight() const { return m_posX + m_width / 2; }
	int GetBottom() const { return m_posY + m_height / 2; }

private:
	// 中心座標と幅、高さで管理する
	int m_posX;		// m_centerXみたいなのも良い
	int m_posY;
	int m_width;
	int m_height;

	// 色
	unsigned int m_color;
	// 塗りつぶしフラグ
	bool m_isFill;

	// マウス追従フラグ
	bool m_isMouseTrase;
};