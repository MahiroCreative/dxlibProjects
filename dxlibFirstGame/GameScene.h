#pragma once
#include "SceneBase.h"
#include "MyGameLib.h"
#include "Player.h"
#include "DxLib.h"

class GameScene : public SceneBase
{
private:
	/*�����o�ϐ�*/
	Player* p_player;
public:
	/*�R���X�g���N�^*/
	GameScene()
	{
		/*�����o������*/
		p_player = new Player();
	}
	/*�����o�֐�*/
	//frame���̌v�Z����
	SceneBase::SceneKind Update() override
	{
		//Player
		p_player->Update();


		//debug.
		if (CheckHitKey(KEY_INPUT_RETURN)) { return SceneKind::titleScene; }

		return SceneKind::gameScene;
	}
	//frame���̕`�揈��
	void Draw() const override
	{
		//Player
		p_player->Draw();
	}
};

