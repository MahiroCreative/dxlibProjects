#pragma once
#include "GameCommon.h"
#include "DxLib.h"
#include "MyGameLib.h"


class GameScene
{
private:
	/*メンバ変数*/
	SceneKind _nextScene;//シーン更新用
	IntVector _charaPos;//キャラクタの位置
	IntVector _charaColPos;//キャラクタのコリジョンの位置
	IntVector _bulletPos;//弾丸の位置
	IntVector _bulletColPos;//弾丸のコリジョンの位置
	int _charaHandle;//キャラの画像ハンドル
	int _charaSpeed;//キャラの移動速度
	int _charaColR;//キャラコリジョンの半径
	int _bulletColR;//弾丸コリジョンの半径
	int _debugInt;//Debug用
	int _time;
	bool _isHitFlag;//当たり判定フラグ
public:
	/*コンストラクタ*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_charaPos(240, 240),
		_charaColPos(_charaPos.X + 23, _charaPos.Y + 20),
		_charaColR(16),
		_charaHandle(-1),
		_charaSpeed(4),
		_bulletPos(800,320),
		_bulletColPos(800, 320),
		_bulletColR(8),
		_isHitFlag(false)
	{
		_charaHandle = LoadGraph("Chara.png");
	};
	/*メンバ関数*/
	//処理の更新
	SceneKind Update()
	{

		/*キャラ更新*/
		//移動操作
		//up.
		if (MyKeyInput::isHoldKey(KEY_INPUT_UP) && _charaPos.Y > 0)
		{
			_charaPos.Y -= _charaSpeed;
		}
		//down.
		if (MyKeyInput::isHoldKey(KEY_INPUT_DOWN) && _charaPos.Y < 680)
		{
			_charaPos.Y += _charaSpeed;
		}
		//left.
		if (MyKeyInput::isHoldKey(KEY_INPUT_LEFT))
		{
			_charaPos.X -= _charaSpeed;
		}
		//right.
		if (MyKeyInput::isHoldKey(KEY_INPUT_RIGHT))
		{
			_charaPos.X += _charaSpeed;
		}
		//コリジョン位置の更新
		_charaColPos.X = _charaPos.X + 23;
		_charaColPos.Y = _charaPos.Y + 20;

		/*弾丸更新*/
		//弾丸1:移動
		_bulletPos.X -= 8;
		_bulletColPos.X -= 8;
		//弾丸2:移動
		//弾丸3:移動

		/*キャラ当たり判定*/
		int HitLength = _charaColR + _bulletColR;
		IntVector delVec = _charaColPos - _bulletColPos;
		int delLength = delVec.Length();
		//hitCount = delLength;
		
		if (HitLength > delLength)
		{
			_isHitFlag = true;
		}
		else
		{
			_isHitFlag = false;
		}

		_time = MyKeyInput::HoldKeyTime(KEY_INPUT_Z);

		/*シーン遷移処理*/
		//Enterキーを押したらTitleシーンに遷移
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}

		return _nextScene;
	}
	//描画更新
	void Draw()
	{
		//現在のシーン名を描画
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));

		//キャラクターの描画
		DrawGraph(_charaPos.X, _charaPos.Y, _charaHandle, TRUE);

		//キャラクターのコリジョンの描画
		DrawCircle(_charaColPos.X, _charaColPos.Y, _charaColR, GetColor(0,255,0), 0);

		//弾丸の描画
		DrawCircle(_bulletPos.X,_bulletPos.Y,8, GetColor(255, 0, 0),1);

		//弾丸のコリジョンの描画
		DrawCircle(_bulletColPos.X, _bulletColPos.Y, _bulletColR, GetColor(0, 0, 255), 0);
	}
	//デバッグ用の描画更新
	void DebugDraw()
	{
		DrawFormatString(10,700,GetColor(0,0,255), "%d", _isHitFlag);
		DrawFormatString(30, 700, GetColor(0, 0, 255), "%d", _time);
	}
	/// <summary>
	/// インスタンスの初期化
	/// </summary>
	void Init()
	{
		//メンバ変数の初期化
		_nextScene = SceneKind::GAMESCENE;
	}
};