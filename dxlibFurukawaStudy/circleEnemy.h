#pragma once

class Enemy
{
public:
	Enemy();	// コンストラクタ
	~Enemy();	// デストラクタ

	void Init();					// 初期化
	void Update();						// 毎フレームの更新
	void Draw();			// 描画
	void SetPosX(int x);
	int GetPosX() const { return m_posX; }		// 値の読み取り:X座標
	int GetPosY() const { return m_posY; }		// 値の読み取り:Y座標
	int GetMoveX() const { return m_moveX; }		// 値の読み取り:Y座標
	int GetMoveY() const { return m_moveY; }		// 値の読み取り:Y座標
	int GetRadius() const { return m_radius; }	// 値の読み取り:半径

	bool GetIsHit() const { return m_isHit; }
	void ChangIsHit() { m_isHit = !m_isHit; }

	int GetChangTime() const { return m_changTime; }
	int GetDelayChangTime() const;

private:
	int m_posX;		// X座標
	int m_posY;		// Y座標
	int m_radius;	// 半径
	bool m_isHit;
	int m_moveX;
	int m_moveY;

	int m_changTime;
};
