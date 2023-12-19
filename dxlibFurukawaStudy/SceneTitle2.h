#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw() const;

	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const { return m_isSceneEnd && (m_fadeAlpha >= 255); }

private:
	// 背景ハンドル
	int m_bgHandle;

	// BGMハンドル
	int m_bgmHandle;

	// 効果音ハンドル
	int m_decideSe;


	bool m_isSceneEnd;	// シーン終了フラグ
	// true :タイトルを終了してゲームへ

// フェードイン、アウト
	int m_fadeAlpha;
};