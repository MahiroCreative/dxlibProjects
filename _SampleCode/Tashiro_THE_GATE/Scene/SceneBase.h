#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class SceneManager;
class FileBase;
class Input;

enum class SceneKind
{
	TITLE,	// タイトル
	STAGE_SELECT,	// ステージセレクト
	MAIN,	// プレイ画面
	CLEAR,	// クリア画面
	OPTION,	// オプション
	DEBUG,	// デバッグ
	MAX
};

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneKind kind);
	virtual ~SceneBase() {}

	/// <summary>
	/// シーンに入るときの初期化処理
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 毎フレーム行う更新処理
	/// </summary>
	/// <param name="isFade">true:フェードしている /false:フェードしていない</param>
	virtual void Update(bool isFade) = 0;
	/// <summary>
	/// 毎フレーム行う描画処理
	/// </summary>
	virtual void Draw() const = 0;
	/// <summary>
	/// シーンを抜けるときの処理
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 現在のシーンの種類
	/// </summary>
	/// <returns>シーンの種類</returns>
	SceneKind GetNowKind() const { return m_nowSceneKind; }

protected:
	SceneManager& m_scnMgr;
	std::unordered_map<std::wstring, std::shared_ptr<FileBase>> m_files;
	
private:
	SceneKind m_nowSceneKind;
};

