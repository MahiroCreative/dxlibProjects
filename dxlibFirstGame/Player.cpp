#include "Player.h"
#include "DxLib.h"
#include "GameCommon.h"

Player::Player()
{
	_pos = IntVector();
	_drawHandle = LoadGraph("Resources/player.png");
}
//frame���̌v�Z����
void Player::Update()
{
	_pos.X += 1;
	_pos.Y += 1;
}
//frame���̕`�揈��
void Player::Draw()
{
	DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
}
//frame���̉�������
void Player::Sound()
{

}