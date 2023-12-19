#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;	// const関数の中ではメンバー変数を変更できない

	// グラフィックを設定
	void SetHandle(int handle);
	// 初期位置の決定	画面内にランダムに配置する
	// グラフィックサイズを見て画面内に収まるようにするので
	// SetHandle()してから呼ぶ
	void SetStartPos();

private:
	int m_handle;	// グラフィックハンドル
	// グラフィックのサイズ
	int m_graphWidth;	// グラフィックの幅
	int m_graphHeight;	// グラフィックの高さ

	int m_posX;
	int m_posY;

	int m_moveX;	// 移動方向
};