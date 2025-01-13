#include "SceneTitle.h"

/*メンバ関数*/
//初期化
void SceneTitle::Init()
{
	/*処理変数の初期化*/
	_arrowTimer = 0;
	_arrowTimerSwitch = false;
	_arrowShowTime = 60;
	_arrowDeleteTime = 30;

	/*ポインタの初期化*/
	//矢印
	_arrow = std::make_unique<SimpleText>();
	//シューティングゲーム
	_shootingGameText = std::make_unique<SimpleText>();
	//プラットフォームゲーム
	_platformGameText = std::make_unique<SimpleText>();
	//ゲーム終了
	_endGameText = std::make_unique<SimpleText>();

	/*オブジェクトの初期化*/
	//矢印
	_arrow->Init("->");
	//シューティングゲーム
	_shootingGameText->Init("ShootingGame");
	//プラットフォームゲーム
	_platformGameText->Init("PlatformGame");
	//ゲーム終了
	_endGameText->Init("EndGame");

	/*オブジェクトの位置設定*/
	//矢印
	_arrow->Transform.Position = Vector2(100.0f, 100.0f);
	//シューティングゲーム
	_shootingGameText->Transform.Position = Vector2(100.0f, 200.0f);
	//プラットフォームゲーム
	_platformGameText->Transform.Position = Vector2(100.0f, 300.0f);
	//ゲーム終了
	_endGameText->Transform.Position = Vector2(100.0f, 400.0f);
}

void SceneTitle::Update()
{
	//矢印の更新
	ArrowUpdate();

}

void SceneTitle::Draw()
{
	/*オブジェクトの描画*/
	//矢印
	_arrow->Draw();
	//シューティングゲーム
	_shootingGameText->Draw();
	//プラットフォームゲーム
	_platformGameText->Draw();
	//ゲーム終了
	_endGameText->Draw();
}

void SceneTitle::ArrowUpdate()
{
	//タイマの更新
	_arrowTimer++;

	
	//矢印の表示切替
	if (_arrow->Visible)//矢印が表示されている
	{
		//60frameで消す
		if (_arrowTimer > 60)
		{
			_arrow->Visible = false;
			_arrowTimerSwitch = true;
		}

	}
	else//矢印が表示されていない
	{
		//30frameで表示
		if (_arrowTimer > 30)
		{
			_arrow->Visible = true;
			_arrowTimerSwitch = true;
		}
	}

	//タイマの初期化
	if (_arrowTimerSwitch)
	{
		_arrowTimer = 0;
		_arrowTimerSwitch = false;
	}
}
