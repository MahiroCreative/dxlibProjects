#pragma once
//Scene.
#include "SceneBase.h"
#include "SceneManager.h"
//lib.
#include "MyGameLib.h"
#include "DxLib.h"
//gameObject.
#include "Player.h"


class GameScene : public SceneBase
{
private:
	/*�����o�ϐ�*/
	Player* p_player;
	SceneBase::SceneKind _nextScene;
public:
	/*�R���X�g���N�^*/
	GameScene()
	{
		/*�����o������*/
		p_player = new Player();
		_nextScene = SceneBase::SceneKind::gameScene;
	}
	/*�����o�֐�*/
	//frame���̌v�Z����
	SceneBase::SceneKind Update() override
	{
		//Player
		p_player->Update();

		//debug.
		//if (CheckHitKey(KEY_INPUT_RETURN)) { return SceneKind::titleScene; }
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN)) { _nextScene = SceneKind::titleScene; }

		return _nextScene;
	}
	//frame���̕`�揈��
	void Draw() const override
	{
		//Player
		p_player->Draw();
	}
};

