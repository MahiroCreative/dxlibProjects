#include "SceneMain.h"
#include "SceneBase.h"
#include "GameCommon.h"
#include "Player.h"
#include "DxLib.h"

/*�R���X�g���N�^*/
SceneMain::SceneMain():
	m_player()
{

}

/*�����o�֐�*/
//frame���̌v�Z����
void SceneMain::Update() const
{
	//Player
}
//frame���̕`�揈��
void SceneMain::Draw() const
{
	//Player
	DrawGraph();
	m_player->m_drawHandle;

}
//frame���̉�������
void SceneMain::Sound() const
{
	
}