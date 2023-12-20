#pragma once
#include "Game.h"

class SceneMapEdit
{
public:
	SceneMapEdit();
	~SceneMapEdit();

	void Init();
	void End();

	void Update();
	void Draw() const;

private:
	// 定数(今回手抜き 本来はBg.hをインクルードするほうが良い)
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	// カーソルの移動
	void CursorUp(bool isLoop);
	void CursorDown(bool isLoop);
	void CursorLeft(bool isLoop);
	void CursorRight(bool isLoop);

	// チップの移動
	void ChipUp(bool isLoop);
	void ChipDown(bool isLoop);

	// グラフィックに存在するマップチップの数
	int GetGraphChipNum();

	// テキストファイルとしてマップチップのデータを出力
	void OuteputText();

	// テキストファイル読み込みのテスト
	void InputText();

	// バイナリデータとしてマップデータを出力
	void OutputBinary();

	// バイナリデータを読み込んでマップとして使用する
	void InputBinary();

private:
	// グラフィックのハンドル
	int m_bgHandle;
	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];

	// カーソル位置 二次元配列のインデックスをデータとして持つ
	int m_cursorX;
	int m_cursorY;

	// カーソル移動のリピート処理
	int m_upRepeatFrame;
	int m_downRepeatFrame;
	int m_leftRepeatFrame;
	int m_rightRepeatFrame;

	// チップデータ変更のリピート処理
	int m_upChipRepeatFrame;
	int m_downChipRepeatFrame;
};