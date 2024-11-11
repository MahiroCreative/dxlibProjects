#include "SceneOption.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "CursorUtility.h"
#include "UIUtility.h"
#include "Game.h"
#include "File.h"
#include "SceneManager.h"
#include "SceneStageSelect.h"
#include "SoundManager.h"

namespace
{
	// 選択種類
	enum class SelectTitleCurrent : int
	{
		BGM,
		SE,
		CLOSE,
		MAX,
	};
	enum class SelectMainCurrent : int
	{
		BGM,
		SE,
		RESTART,
		RETURN_STAGE_SELECT,
		MAX
	};
	// 確認種類
	enum class CheckMainCurrent : int
	{
		CANCEL,
		RETURN,
		MAX
	};
	// 音変更
	enum class SoundChange
	{
		BGM,
		SE,
	};

	// ファイルID
	const wchar_t* const FILE_WINDOW				= L"I_OptionWindow";
	const wchar_t* const FILE_COMMON_FRAME			= L"I_CommonFrame";
	const wchar_t* const FILE_COMMON_SELECT_FRAME	= L"I_CommonSelectFrame";
	const wchar_t* const FILE_SOUND_BAR				= L"I_MainSoundBar";
	const wchar_t* const FILE_VOLUME_POINT			= L"I_VolumePoint";

	// フレーム描画位置
	constexpr int DRAW_FRAME_X = 350;
	constexpr int DRAW_FRAME_Y = 200;
	// フレーム描画間隔
	constexpr int DRAW_FRAME_Y_INTERVAL = 80;
	// ウィンドウ画像サイズ
	constexpr float FILE_SIZE_WINDOW = 0.8f;
	// フレーム画像サイズ
	constexpr float FILE_SIZE_FRAME = 0.75f;
	// フォントサイズ
	constexpr int FONT_SIZE = 32;
	// 選択文字カラー
	constexpr unsigned int COLOR_SELECT = 0x000000;
	// 未選択文字カラー
	constexpr unsigned int COLOR_NOT_SELECT = 0xffffff;
	// タイトルから来た時の文字列
	const std::vector<std::wstring> STR_TITLE =
	{
		L"ＢＧＭ",
		L"ＳＥ",
		L"閉じる"
	};
	// メインからの来た時の文字列
	const std::vector<std::wstring> STR_MAIN =
	{
		L"ＢＧＭ",
		L"ＳＥ",
		L"再開",
		L"ステージ選択へ",
	};

	// 変更音量
	constexpr int CHANGE_VOLUME = 1;
}

SceneOption::SceneOption() :
	SceneBase(SceneKind::OPTION),
	m_updateFunc(&SceneOption::TitleUpdate),
	m_mainUpdateFunc(&SceneOption::SelectMainUpdate),
	m_openScene(SceneKind::TITLE),
	m_selectCurrent(0),
	m_checkCurrent(0),
	m_isCheck(false)
{
}

void SceneOption::Init()
{
	auto& fileMgr = FileManager::GetInstance();
	m_files[FILE_WINDOW]				= fileMgr.Load(FILE_WINDOW);
	m_files[FILE_COMMON_FRAME]			= fileMgr.Load(FILE_COMMON_FRAME);
	m_files[FILE_COMMON_SELECT_FRAME]	= fileMgr.Load(FILE_COMMON_SELECT_FRAME);
	m_files[FILE_SOUND_BAR]				= fileMgr.Load(FILE_SOUND_BAR);
	m_files[FILE_VOLUME_POINT]			= fileMgr.Load(FILE_VOLUME_POINT);

	m_selectStrList[SceneKind::TITLE] = STR_TITLE;
	m_selectStrList[SceneKind::MAIN] = STR_MAIN;

	constexpr int DRAW_SOUND_X = 800;
	constexpr int DRAW_SOUND_Y = 200;
	m_soundUI = std::make_shared<UIMoveData>();
	*m_soundUI = UIMoveData::Make(DRAW_SOUND_X, DRAW_SOUND_Y);
}

void SceneOption::Update(bool isFade)
{
	(this->*m_updateFunc)();
}

void SceneOption::Draw() const
{
	int selectH = m_files.at(FILE_COMMON_SELECT_FRAME)->GetHandle();
	int notSelectH = m_files.at(FILE_COMMON_FRAME)->GetHandle();
	DrawRotaGraphFast(Game::CENTER_X, Game::CENTER_Y, FILE_SIZE_WINDOW, 0.0f, m_files.at(FILE_WINDOW)->GetHandle(), true);
	UIUtility::DrawFrameAndStr(m_uiList, FILE_SIZE_FRAME, 0.0f, FONT_SIZE, m_selectCurrent, m_selectStrList.at(m_openScene), selectH, notSelectH, COLOR_SELECT, COLOR_NOT_SELECT);
	// TODO: 音量バー
//	DrawSoundBar();
//	DrawSoundBar();
	if (!m_isCheck) return;
	DrawBox(480 + 160 * m_checkCurrent, 128, 640 + 160 * m_checkCurrent, 144, 0xff0000, true);
	DrawString(480, 128, L"キャンセル", 0xffffff);
	DrawString(640, 128, L"ステージ選択へ", 0xffffff);
}

void SceneOption::End()
{
}

void SceneOption::CheckOpenScene(SceneKind openScene)
{
	m_openScene = openScene;
	if (openScene == SceneKind::TITLE)
	{
		m_uiList = UIMoveData::Make(static_cast<int>(SelectTitleCurrent::MAX), DRAW_FRAME_X, DRAW_FRAME_Y, 0, DRAW_FRAME_Y_INTERVAL);

		m_updateFunc = &SceneOption::TitleUpdate;
	}
	else if (openScene == SceneKind::MAIN)
	{
		m_uiList = UIMoveData::Make(static_cast<int>(SelectMainCurrent::MAX), DRAW_FRAME_X, DRAW_FRAME_Y, 0, DRAW_FRAME_Y_INTERVAL);

		m_updateFunc = &SceneOption::MainUpdate;
	}
	else
	{
		assert(false && "開くシーンがおかしいです");
	}
}

void SceneOption::TitleUpdate()
{
	CursorUtility::CursorUp<SelectTitleCurrent>(m_selectCurrent, SelectTitleCurrent::MAX);
	CursorUtility::CursorDown<SelectTitleCurrent>(m_selectCurrent, SelectTitleCurrent::MAX);

	auto& input = Input::GetInstance();
	// 決定
	if (input.IsTriggerd(Command::BTN_OK))
	{
		// 閉じる
		if (m_selectCurrent == static_cast<int>(SelectTitleCurrent::CLOSE))
		{
			m_scnMgr.CloseOption();
		}
	}
	// キャンセル
	else if (input.IsTriggerd(Command::BTN_CANCEL))
	{
		// 閉じる
		m_scnMgr.CloseOption();
	}
}

void SceneOption::MainUpdate()
{
	(this->*m_mainUpdateFunc)();
}

void SceneOption::SelectMainUpdate()
{
	CursorUtility::CursorUp<SelectMainCurrent>(m_selectCurrent, SelectMainCurrent::MAX);
	CursorUtility::CursorDown<SelectMainCurrent>(m_selectCurrent, SelectMainCurrent::MAX);

	auto& input = Input::GetInstance();
	// 決定
	if (input.IsTriggerd(Command::BTN_OK))
	{
		// 再開
		if (m_selectCurrent == static_cast<int>(SelectMainCurrent::RESTART))
		{
			m_scnMgr.CloseOption();
		}
		// ステージ選択に戻る
		else if (m_selectCurrent == static_cast<int>(SelectMainCurrent::RETURN_STAGE_SELECT))
		{
			m_mainUpdateFunc = &SceneOption::CheckMainUpdate;
			m_checkCurrent = 0;
			m_isCheck = true;
		}
	}
	// キャンセル
	else if (input.IsTriggerd(Command::BTN_CANCEL))
	{
		// 閉じる(再開)
		m_scnMgr.CloseOption();
	}
}

void SceneOption::CheckMainUpdate()
{
	CursorUtility::CursorUp<CheckMainCurrent>(m_checkCurrent, CheckMainCurrent::MAX, Command::BTN_LEFT);
	CursorUtility::CursorDown<CheckMainCurrent>(m_checkCurrent, CheckMainCurrent::MAX, Command::BTN_RIGHT);

	auto& input = Input::GetInstance();
	// 決定
	bool isCancel = false;
	if (input.IsTriggerd(Command::BTN_OK))
	{
		// 戻る
		if (m_checkCurrent == static_cast<int>(CheckMainCurrent::RETURN))
		{
			auto next = std::make_shared<SceneStageSelect>();
			m_scnMgr.Change(next);
			m_scnMgr.CloseOption();
		}
		// キャンセル
		else if (m_checkCurrent == static_cast<int>(CheckMainCurrent::CANCEL))
		{
			isCancel = true;
		}
	}
	// キャンセル
	else if (input.IsTriggerd(Command::BTN_CANCEL))
	{
		isCancel = true;
	}

	if (isCancel)
	{
		m_mainUpdateFunc = &SceneOption::CheckMainUpdate;
		m_isCheck = false;
	}
}

void SceneOption::DrawSoundBar(int y, int volume) const
{

}

void SceneOption::SoundChangeUpdate(int current)
{
	auto& input = Input::GetInstance();
	auto& sndMgr = SoundManager::GetInstance();

	// それぞれに合った方の現在のボリュームを取得
	int volume = 0;
	if (current == static_cast<int>(SoundChange::BGM))
	{
		volume = sndMgr.GetBgmVol();
	}
	else if (current == static_cast<int>(SoundChange::SE))
	{
		volume = sndMgr.GetSeVol();
	}

	// 音量減少
	if (input.IsRepeat(Command::BTN_LEFT))
	{
		volume -= CHANGE_VOLUME;
	}
	// 音量増加
	if (input.IsRepeat(Command::BTN_RIGHT))
	{
		volume += CHANGE_VOLUME;
	}

	// それぞれに合わせて変更したボリュームを設定
	if (current == static_cast<int>(SoundChange::BGM))
	{
		sndMgr.ChangeBgmVol(volume);
	}
	else if (current == static_cast<int>(SoundChange::SE))
	{
		sndMgr.ChangeSeVol(volume);
	}
}
