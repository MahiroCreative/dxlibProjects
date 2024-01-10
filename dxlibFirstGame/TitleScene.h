#pragma once
#include "SceneBase.h"

class TitleScene :
	public SceneBase
{
private:
	IntVector _arrowPos;
	IntVector _movePos;
	IntVector _tempPos;
	int _inputTime;
	int _bgmHandle;
	SceneBase::SceneKind _nextScene;
public:
	/*コンストラクタ*/
	TitleScene()
	{
		/*変数初期化*/
		_arrowPos = IntVector(560,480);
		_movePos = IntVector(560,520);
		_tempPos = IntVector();
		_inputTime = -1;
		_nextScene = SceneKind::titleScene;
		_bgmHandle = LoadSoundMem("Resources/bgm_title.mp3");
		/*初期実行*/
		//BGM再生
		PlaySoundMem(_bgmHandle, DX_PLAYTYPE_BACK);
	}
	/*メンバ関数*/
	//frame毎の計算処理
	SceneBase::SceneKind Update() override
	{
		/*Key入力操作(超雑作り直せ)*/
		if (_inputTime == -1)
		{
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
			{
				//入れ替え
				_tempPos = _arrowPos;
				_arrowPos = _movePos;
				_movePos = _tempPos;
				//タイマ更新
				_inputTime = 0;
			}
			else if (CheckHitKey(KEY_INPUT_RETURN))
			{
				if (_arrowPos.Y == 520)
				{
					_nextScene = SceneKind::gameEnd;
				}
				else
				{
					_nextScene = SceneKind::gameScene;
				}

			}

		}
		else if (_inputTime < 8 && _inputTime != -1)
		{
			_inputTime += 1;
		}
		else
		{
			_inputTime = -1;
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