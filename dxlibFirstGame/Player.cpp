#include "Player.h"
#include "DxLib.h"
#include "GameCommon.h"

Player::Player()
{
	_pos = Vector();
	_drawHandle = LoadGraph("Resources/player.png");
}
//frame���̌v�Z����
void Player::Update()
{
	_pos.X += 0.1f;
	_pos.Y += 0.1f;
}
//frame���̕`�揈��
void Player::Draw()
{
	DrawGraphF(_pos.X, _pos.Y, _drawHandle, false);
}
//frame���̉�������
void Player::Sound()
{

}