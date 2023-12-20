#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"


class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw() const;
	void End();		// シーンの終了処理

	// シーンを終了させるかどうか
	bool IsSceneEnd() const;

private:
	// 画面内に同時に存在できる敵の最大数
	static constexpr int kEnemyMax = 16;

private:
	int m_playerHandle;	// プレイヤーのグラフィック
	int m_enemyHandle;	// 敵のグラフィック
	int m_bgHandle;		// 背景のグラフィック

	int m_bgmHandle;	// BGM

	int m_enemyStartSe;	// 敵の落ちるSE
	int m_hitSe;		// あった時のSE
	int m_walkSe;		// 歩く時のSE

	// このクラスが呼ばれた時点でメンバ変数のクラスはコンストラクタを呼ばれるため
	// このクラスのコンストラクタで初期化しなくてもよい
	// が明示しておくほうが良いため
	// m_player() と引数なしでコンストラクタに書いておく
	Player m_player;
	Enemy m_enemy[kEnemyMax];

	bool m_isGameOver;		// ゲームオーバーかどうかのフラグ
	bool m_isSceneEnd;		// シーンを終了する時にtrueにする
	int m_playFrameCount;	// 生き残っている時間

	// 雨粒の生成制御
	int m_enemyCreateNum;	// 今までに生産した敵の数
	int m_enemyWaitFrame;	// 敵生成までの待ち時間

	// フェードイン、アウト
	int m_fadeAlpha;
};