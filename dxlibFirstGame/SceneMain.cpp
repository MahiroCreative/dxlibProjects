#include "SceneMain.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*�R���X�g���N�^*/
SceneMain::SceneMain()
{
	/*�����o������*/
	p_player = new Player();
}

/*�����o�֐�*/
//frame���̌v�Z����
void SceneMain::Update() const
{
	//Player
	p_player->Update();
}
//frame���̕`�揈��
void SceneMain::Draw() const
{
	//Player
	p_player->Draw();

}
//frame���̉�������
void SceneMain::Sound() const
{
	
}