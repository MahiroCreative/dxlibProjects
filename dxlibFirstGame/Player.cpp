#include "Player.h"
#include "DxLib.h"
#include "GameCommon.h"

Player::Player()
{
	_pos = IntVector();
	_drawHandle = LoadGraph("Resources/player.png");
}
//frame–ˆ‚ÌŒvZˆ—
void Player::Update()
{
	_pos.X += 1;
	_pos.Y += 1;
}
//frame–ˆ‚Ì•`‰æˆ—
void Player::Draw()
{
	DrawGraph(_pos.X, _pos.Y, _drawHandle, false);
}
//frame–ˆ‚Ì‰¹ºˆ—
void Player::Sound()
{

}