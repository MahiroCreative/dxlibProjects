#pragma once
#include "SceneBase.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

class GameScene : public SceneBase
{
public:
	/*�R���X�g���N�^*/
	GameScene()
	{
		/*�����o������*/
		p_player = new Player();
	}
	/*�����o�֐�*/
	//frame���̌v�Z����
	void Update() const override
	{
		//Player
		p_player->Update();
	}
	//frame���̕`�揈��
	void Draw() const override
	{
		//Player
		p_player->Draw();
	}
	//frame���̉�������
	void Sound() const override
	{
		p_player->Sound();
	}
private:
	/*�����o�ϐ�*/
	Player* p_player;
};

