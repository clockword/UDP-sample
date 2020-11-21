#include "Player.h"

void Player::MoveInput(DWORD tick)
{
	BYTE key[256];

	::GetKeyboardState(key);

	if (key[VK_LEFT] & 0x80)
	{
		SetAniKind(ANIKIND::LEFT);
		Translate(-speed * (int)(tick * 0.1), 0);
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		SetAniKind(ANIKIND::RIGHT);
		Translate(speed * (int)(tick * 0.1), 0);
	}
	else if (key[VK_UP] & 0x80)
	{
		SetAniKind(ANIKIND::UP);
		Translate(0, -speed * (int)(tick * 0.1));
	}
	else if (key[VK_DOWN] & 0x80)
	{
		SetAniKind(ANIKIND::DOWN);
		Translate(0, speed * (int)(tick * 0.1));
	}
}

Player::Player() : GameObject()
{
	speed = 0;
}

Player::~Player()
{
}

void Player::Update(Graphics* g, DWORD tick)
{
	MoveInput(tick);

	UpdateAnim(tick);
	Draw(g);
}
