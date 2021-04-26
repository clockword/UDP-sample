#include "Player.h"

void Player::MoveInput(DWORD tick)
{
	BYTE key[256];

	::GetKeyboardState(key);

	if (key[VK_LEFT] & 0x80)
	{
		SetAniKind(static_cast<DWORD>(ANIKIND::LEFT));
		SetVelocity(Vector2::Left() * 100.0f);
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		SetAniKind(static_cast<DWORD>(ANIKIND::RIGHT));
		SetVelocity(Vector2::Right() * 100.0f);
	}
	else if (key[VK_UP] & 0x80)
	{
		SetAniKind(static_cast<DWORD>(ANIKIND::UP));
		SetVelocity(Vector2::Up() * 100.0f);
	}
	else if (key[VK_DOWN] & 0x80)
	{
		SetAniKind(static_cast<DWORD>(ANIKIND::DOWN));
		SetVelocity(Vector2::Down() * 100.0f);
	}
	else
	{
		SetVelocity(Vector2::Zero());
	}
}

void Player::Init()
{
	CollObject::Init();
}

void Player::Update(Graphics* g, DWORD tick)
{
	CollObject::Update(g, tick);
	MoveInput(tick);
}
