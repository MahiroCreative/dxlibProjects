#pragma once
#include "SceneBase.h"
#include "SceneManager.h"

class TitleScene :
	public SceneBase
{
private:
	IntVector _arrowPos;
	IntVector _movePos;
	IntVector _tempPos;
	int _inputTime;
	int _bgmHandle;
	int _nextScene;
public:
	/*コンストラクタ*/
	TitleScene()
	{
		/*変数初期化*/
		_arrowPos = IntVector(560,480);
		_movePos = IntVector(560,520);
		_tempPos = IntVector();
		_inputTime = -1;
		_nextScene = SceneKind::TITLESCENE;
		_bgmHandle = LoadSoundMem("Resources/bgm_title.mp3");
		/*初期実行*/
		//BGM再生
		PlaySoundMem(_bgmHandle, DX_PLAYTYPE_BACK);
	}
	/*メンバ関数*/
	//frame毎の計算処理
	int Update() override
	{
		/*Key入力の確認*/
		MyKeyInput::Update();

		/*入力操作*/
		//上下キー
		if (MyKeyInput::isDownKey(KEY_INPUT_UP) || MyKeyInput::isDownKey(KEY_INPUT_DOWN))
		{
			//入れ替え
			_tempPos = _arrowPos;
			_arrowPos = _movePos;
			_movePos = _tempPos;
		}
		//エンターキー
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			//矢印の位置でシーン遷移先を変更
			if (_arrowPos.Y == 520)
			{
				_nextScene = SceneKind::GAMESCENE;
			}
			else
			{
				_nextScene = SceneKind::ENDGAME;
			}
		}

		/*返り値*/
		return _nextScene;
	}
	//frame毎の描画処理
	void Draw() const override
	{
		/*文字の描画*/
		//Start.
		DrawString(600, 480, "START", GetColor(255, 255, 255));
		//End.
		DrawString(600, 520, "END", GetColor(255, 255, 255));
		//Arrow.
		DrawString(_arrowPos.X, _arrowPos.Y, "→", GetColor(255, 255, 255));
	}
};