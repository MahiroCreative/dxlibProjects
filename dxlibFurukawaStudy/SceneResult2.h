#pragma once

class SceneResult
{
public:
	SceneResult();
	~SceneResult();

	void Init();
	void Update();
	void Draw();

	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const { return m_isSceneEnd && (m_fadeAlpha >= 255); }

private:
	// 画像のハンドル
	int m_gameOverHandle;
	int m_bgHandle;
	// サウンドハンドル
	int m_bgmHandle;
	int m_decideSe;

	// 画像サイズ
	int m_graphWidth;
	int m_graphHeight;

	int m_lastPad;		// 前回のパッド情報
	bool m_isSceneEnd;	// シーン終了フラグ

	// フェードイン、アウト
	int m_fadeAlpha;
};