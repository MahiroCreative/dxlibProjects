#include "Player.h"
#include "DxLib.h"
#include "GameCommon.h"

Player::Player()
{
	_pos = Vector();
	_drawHandle = LoadGraph("Resources/player.png");
}
//frame–ˆ‚ÌŒvZˆ—
void Player::Update()
{
	_pos.X += 0.1f;
	_pos.Y += 0.1f;
}
//frame–ˆ‚Ì•`‰æˆ—
void Player::Draw()
{
	DrawGraphF(_pos.X, _pos.Y, _drawHandle, false);
}
//frame–ˆ‚Ì‰¹ºˆ—
void Player::Sound()
{

}