#pragma once

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	static const int kBgNum = 4;

private:

	int m_bgHandle[4];	// bg -> background
	int m_bgNo;			// 現在表示しているBGの番号
	// No	現在の番号
	// Num	総数


	int m_fadeCount;	// フェード度合		0:透明　、フェードインしきった状態(ゲーム画面が見えている)
	//				　255:不透明、フェードアウトしきった状態(真っ暗)

	int m_fadeSpeed;	// フェードスピード
	int m_waitFrame;	// フェードインしきった後の待ち時間
};