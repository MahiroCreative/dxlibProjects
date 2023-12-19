#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;

	// グラフィックの指定
	void SetGraphHandle(int handle);

	// 敵キャラクターの開始処理
	// 画面上から落ち始める
	void Start();

	// 存在するかチェック
	bool IsExist() const { return m_isExist; }

	// 敵キャラクターの初期位置設定
	void SetStartPos();

	float GetLeft() const { return m_posX[0]; }
	float GetRight() const { return m_posX[0] + m_graphWidth; }
	float GetUp() const { return m_posY[0]; }
	float GetDown() const { return m_posY[0] + m_graphHeight; }

private:
	// 残像用に保存する位置情報の数
	static constexpr int kPosLogFrame = 8;

private:
	int m_handle;
	int m_graphWidth;
	int m_graphHeight;

	// 存在するか
	bool m_isExist;

	// 位置情報
	float m_posX[kPosLogFrame];
	float m_posY[kPosLogFrame];

	// 移動量
	float m_moveY;
};