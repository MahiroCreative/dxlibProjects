#include "GameScene.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*�R���X�g���N�^*/
GameScene::GameScene()
{
	/*�����o������*/
	p_player = new Player();
}

/*�����o�֐�*/
//frame���̌v�Z����
void GameScene::Update() const
{
	//Player
	p_player->Update();
}
//frame���̕`�揈��
void GameScene::Draw() const
{
	//Player
	p_player->Draw();

}
//frame���̉�������
void GameScene::Sound() const
{
	
}