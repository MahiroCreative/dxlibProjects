#include <DxLib.h>
#include <cassert>
// ファイルの出力に使用する
#include <iostream>
#include <fstream>
#include <string>	// 文字列を便利に扱うためのクラス
#include <cstdlib>

#include "SceneMapEdit.h"

#include "Pad.h"


namespace
{
	// カーソル移動のリピートフレーム
	constexpr int kCursorRepeatFrame = 6;

	// チップデータ変更のリピートフレーム
	constexpr int kChipRepeatFrame = 8;
}

SceneMapEdit::SceneMapEdit() :
	m_cursorX(0),
	m_cursorY(0),
	m_upRepeatFrame(0),
	m_downRepeatFrame(0),
	m_leftRepeatFrame(0),
	m_rightRepeatFrame(0),
	m_upChipRepeatFrame(0),
	m_downChipRepeatFrame(0)
{
	// グラフィックのロード
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// マップチップの数を数える
	int graphW;
	int graphH;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	// チップ開始情報の生成
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{		
			m_chipData[y][x] = 0;
		}
	}
}


SceneMapEdit::~SceneMapEdit()
{
	// グラフィックの解放
	DeleteGraph(m_bgHandle);
}

void SceneMapEdit::Init()
{
}

void SceneMapEdit::End()
{
}


void SceneMapEdit::Update()
{
	// 移動処理
	if (Pad::IsRepeat(PAD_INPUT_UP, m_upRepeatFrame, kCursorRepeatFrame))
	{
		CursorUp(Pad::IsTrigger(PAD_INPUT_UP));
	}
	if (Pad::IsRepeat(PAD_INPUT_DOWN, m_downRepeatFrame, kCursorRepeatFrame))
	{
		CursorDown(Pad::IsTrigger(PAD_INPUT_DOWN));
	}
	if (Pad::IsRepeat(PAD_INPUT_LEFT, m_leftRepeatFrame, kCursorRepeatFrame))
	{
		CursorLeft(Pad::IsTrigger(PAD_INPUT_LEFT));
	}
	if (Pad::IsRepeat(PAD_INPUT_RIGHT, m_rightRepeatFrame, kCursorRepeatFrame))
	{
		CursorRight(Pad::IsTrigger(PAD_INPUT_RIGHT));
	}

	// チップ処理
	if (Pad::IsRepeat(PAD_INPUT_1, m_upChipRepeatFrame, kChipRepeatFrame))
	{
		ChipUp(Pad::IsTrigger(PAD_INPUT_1));
	}
	if (Pad::IsRepeat(PAD_INPUT_2, m_downChipRepeatFrame, kChipRepeatFrame))
	{
		ChipDown(Pad::IsTrigger(PAD_INPUT_2));
	}

	// ファイル出力
	if (Pad::IsTrigger(PAD_INPUT_3))	// コントローラーのXボタン, キーボードだと"C"
	{
		OutputBinary();
	}
	
	// ファイル読み込み
	if (Pad::IsTrigger(PAD_INPUT_4))	// コントローラーのYボタン, キーボードだと"a"
	{
		InputBinary();
	}
#if false
	if (false)
	{
		std::fstream file;
		file.open("test.txt", std::ios::in | std::ios::out);	// 複数のフラグを同時に指定可能
	}
#endif
}

void SceneMapEdit::Draw() const
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// マップ情報から置くチップを取ってくる
			int chipNo = m_chipData[y][x];

			// マップチップのグラフィック切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(kChipWidth * x, kChipHeight * y,
				srcX, srcY,
				kChipWidth, kChipHeight,
				m_bgHandle, true);
		}
	}

	// グリッドの表示
	// 縦線
	for (int x = 1; x < kChipNumX; x++)
	{
		DrawLine(x * kChipWidth, 0, x * kChipWidth, Game::kScreenHeight, 0x0000ff);
	}
	// 横線
	for (int y = 1; y < kChipNumY; y++)
	{
		DrawLine(0, y * kChipHeight, Game::kScreenWidth, y * kChipHeight, 0x0000ff);
	}

	// 現在選択しているチップにカーソルを表示
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;
	DrawBox(cursorPosX, cursorPosY,
				cursorPosX + kChipWidth, cursorPosY + kChipHeight,
				0xff0000, false);
	// 一回り小さい四角を描画して線の太い四角にする
	DrawBox(cursorPosX + 1, cursorPosY + 1,
				cursorPosX + kChipWidth - 1, cursorPosY + kChipHeight - 1,
				0xff0000, false);
}

void SceneMapEdit::CursorUp(bool isLoop)
{
	m_cursorY--;

	// トリガーの時のみループ
	if (m_cursorY < 0)
	{
		if (isLoop)	m_cursorY = kChipNumY - 1;
		else		m_cursorY = 0;
	}
}

void SceneMapEdit::CursorDown(bool isLoop)
{
	m_cursorY++;

	if (kChipNumY - 1 < m_cursorY)
	{
		if (isLoop) m_cursorY = 0;
		else		m_cursorY = kChipNumY - 1;
	}
}

void SceneMapEdit::CursorLeft(bool isLoop)
{
	m_cursorX--;

	if (m_cursorX < 0)
	{
		if (isLoop) m_cursorX = kChipNumX - 1;
		else								m_cursorX = 0;
	}
}

void SceneMapEdit::CursorRight(bool isLoop)
{
	// カーソルの移動処理
	m_cursorX++;

	if (kChipNumX - 1 < m_cursorX)
	{
		if (isLoop)
		{
			// トリガーの時はカーソルをループする
			m_cursorX = 0;
		}
		else
		{
			// リピート処理の時は一度止める
			m_cursorX = kChipNumX - 1;
		}
	}
}


void SceneMapEdit::ChipUp(bool isLoop)
{
	assert(0 <= m_cursorX && m_cursorX < kChipNumX);
	assert(0 <= m_cursorY && m_cursorY < kChipNumY);

	// 選択しているマップチップの番号を+1
	m_chipData[m_cursorY][m_cursorX]++;

	if (GetGraphChipNum() - 1 < m_chipData[m_cursorY][m_cursorX])
	{
		if (isLoop)	m_chipData[m_cursorY][m_cursorX] = 0;
		else		m_chipData[m_cursorY][m_cursorX] = GetGraphChipNum() - 1;
	}
}

void SceneMapEdit::ChipDown(bool isLoop)
{
	assert(0 <= m_cursorX && m_cursorX < kChipNumX);
	assert(0 <= m_cursorY && m_cursorY < kChipNumY);

	// 選択しているマップチップの番号を-1
	m_chipData[m_cursorY][m_cursorX]--;

	if (m_chipData[m_cursorY][m_cursorX] < 0)
	{
		if (isLoop)	m_chipData[m_cursorY][m_cursorX] = GetGraphChipNum() - 1;
		else		m_chipData[m_cursorY][m_cursorX] = 0;
	}
}


int SceneMapEdit::GetGraphChipNum()
{
	return m_graphChipNumX * m_graphChipNumY;
}


void SceneMapEdit::OuteputText()
{
	std::fstream file;

	file.open("test.txt", std::ios::out);	// ファイルを開く 出力したいのでstd::ios::out
	// ファイルの内容を見たい場合はstd::ios::inで開く

// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルが開久野に失敗した場合の処理
		// 教科書は開けなかったらその時点でプログラム終了
		// return EXIT_FAILURE;

		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
#if false
		// ファイルが開けた場合の処理
		file << "ファイルに書き込んじゃえ。" << std::endl;	// openしたファイルに書き込み

		// 数値の書き込みテスト
		int num = 256;
		file << num << std::endl;
#endif
		// 作成したマップのデータをテキストで出力する
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{" << std::flush;
			for (int x = 0; x < kChipNumX; x++)
			{
				// 最後のみ","は出力しない
				if (x == kChipNumX - 1) file << m_chipData[y][x] << std::flush;
				else					file << m_chipData[y][x] << "," << std::flush;
			}
			file << "}," << std::endl;
		}

		file.close();

		printfDx("ファイルに書き込みを行いました\n");
	}
}

void SceneMapEdit::InputText()
{
	std::fstream file;

	file.open("test.txt", std::ios::in);	// 読み込むときはstd::ios::inで開く

	// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルが開久野に失敗した場合の処理
		// 教科書は開けなかったらその時点でプログラム終了
		// return EXIT_FAILURE;

		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		// ファイルのオープンに成功したので読み込みを行う
		std::string str;	// 内部にcharの配列を持っている(ようなもの)
		std::getline(file, str);

		file.close();

		printfDx(str.c_str());
	}
}


void SceneMapEdit::OutputBinary()
{
	std::fstream file;

	// バイナリモードで開く
	// 拡張子はなんでもよい　バイナリデータを表すbin, データを表すdat等がメジャー
	file.open("data/map/map.bin", std::ios::out | std::ios::binary);	

	if (!file.is_open())
	{
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		// マップチップの配置データをバイナリで出力
		
		// fstreamのwrite関数を使用して出力する
		// メモリ上のどこに置かているか(アドレス)と
		// そこから何バイト出力するか、を指定する
		file.write((const char*)&m_chipData, sizeof(m_chipData));

		file.close();

		printfDx("バイナリデータとしてマップデータを出力しました\n");
	}
}

void SceneMapEdit::InputBinary()
{
	std::fstream file;

	// バイナリモードで開く
	file.open("data/map/map.bin", std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		// 読み込んだバイナリの内容をメモリ上のマップチップ情報に上書きする
		file.read((char*)&m_chipData, sizeof(m_chipData));

		file.close();

		printfDx("バイナリデータとしてマップデータを入力しました\n");
	}
}
