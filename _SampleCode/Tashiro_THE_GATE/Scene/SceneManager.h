#pragma once
#include <memory>

class SceneBase;
enum class SceneKind;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
private:
	SceneManager();

	SceneManager(const SceneManager& mgr) = delete;
	void operator= (const SceneManager& mgr) = delete;

public:
	virtual ~SceneManager();

	static SceneManager& GetInstance();

	void Init();
	void Update();
	void Draw() const;
	void End();

	/// <summary>
	/// シーンの変更
	/// </summary>
	/// <param name="isFade">true: フェードを行う(default) / false: フェードを行わい</param>
	void Change(const std::shared_ptr<SceneBase>& next, bool isFade = true);

	/// <summary>
	/// 流すBgmを変更する
	/// </summary>
	/// <param name="handle">流すBgmのハンドル</param>
	void ChangeBgmH(int handle);

	/// <summary>
	/// オプションを開く
	/// </summary>
	/// <param name="openScene">開いたシーンの種類</param>
	void OpenOption(SceneKind openScene);
	/// <summary>
	/// オプションorポーズを閉じる
	/// </summary>
	void CloseOption();

	/// <summary>
	/// オプションを開いているか
	/// </summary>
	/// <returns>true:開いている /false:開いていない</returns>
	bool IsOpenOption() const { return m_option != nullptr; }
	SceneKind GetNowSceneKind() const;

private:
	using UpdateFunc_t = void(SceneManager::*)();
	void NormalUpdate();
	void FileLoadingUpdate();

	using DrawFunc_t = void(SceneManager::*)() const;
	void DrawNormal() const;
	void FileLoadingDraw() const;

	// フェードアウトに使うもの
	using FadeFunc_t = void(SceneManager::*)();
	void FadeNone();
	void FadeIn();
	void FadeOut();

	void CheckFileLoadingStart();

private:
	std::shared_ptr<SceneBase> m_option;
	std::shared_ptr<SceneBase> m_scene;
	std::shared_ptr<SceneBase> m_nextScene;

	UpdateFunc_t m_updateFunc;
	DrawFunc_t m_drawFunc;

	// 流しているBGMのハンドル
	int m_bgmH;

	// フェードアウトに使うもの
	FadeFunc_t m_fadeFunc;
	float m_fadeRate;
	bool m_isFade;
};

