#include <DxLib.h>
#include "SceneMain3.h"
// ヘッダーではクラスのプロトタイプ宣言のみ
// ソースファイル内でインクルードを行う
#include "Player3.h"

SceneMain::SceneMain() :
	m_frameCount(0)
{
	// 慣れるまではメンバーのメモリ確保はコンストラクタで
	m_pPlayer = new Player;
}

SceneMain::~SceneMain()
{
	// 慣れるまではメンバーの解放はデストラクタで
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneMain::Init()
{
	//for (int i = 0; i < kPlayerNum; i++)
	m_pPlayer->Init();
}

// 毎フレームの処理
void SceneMain::Update()
{
	m_frameCount++;

	m_pPlayer->Update();
}

// Updateで勝利した結果を反映させた表示をDrawで行う
void SceneMain::Draw() const
{
	// Colorに関して
	// 左2ByteずつでR,G,Bの値を処理していると思われる
	DrawFormatString(8, 8, 0xffffff, "%d", m_frameCount);

	m_pPlayer->Draw();
}
