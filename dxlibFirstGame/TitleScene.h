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
public:
	/*コンストラクタ*/
	TitleScene()
	{
		_arrowPos = IntVector(560,480);
		_movePos = IntVector(560,520);
		_tempPos = IntVector();
		_inputTime = -1;
		_bgmHandle = LoadSoundMem("Resources/bgm_title.mp3");
		//PlaySoundMem(_bgmHandle, DX_PLAYTYPE_NORMAL);
	}
	/*メンバ関数*/
	//frame毎の計算処理
	void Update(SceneBase *nextScene) override
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
				if (_arrowPos.Y ==520)
				{
					DxLib::DxLib_End();//Dxlib終了処理
				}
				else
				{
					nextScene = new GameScene();
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
	//frame毎の音声処理
	void Sound() const override
	{
		
	}
};