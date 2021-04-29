#include "PongBar.h"

void PongBar::Control(DWORD tick)
{
	BYTE key[256];

	::GetKeyboardState(key);

	if (key[VK_LEFT] & 0x80)
	{
		SetAcceleration(Vector2::Left * 10000.0f);
	}
	else if (key[VK_RIGHT] & 0x80)
	{
		SetAcceleration(Vector2::Right * 10000.0f);
	}
	else if (key[VK_UP] & 0x80)
	{
		SetAcceleration(Vector2::Up * 10000.0f);
	}
	else if (key[VK_DOWN] & 0x80)
	{
		SetAcceleration(Vector2::Down * 10000.0f);
	}
	else
	{
		SetAcceleration(Vector2::Zero);
	}
}

CHARMOVE PongBar::GetPacket()
{
	CHARMOVE charMove;
	charMove.curX = GetPosition().X;
	charMove.curY = GetPosition().Y;

	return charMove;
}

void PongBar::Init()
{
	CollObject::Init();
	SetMaxSpeed(100.0f);
	SetFriction(100000.0f);
}

void PongBar::Update(Graphics* g, DWORD tick)
{
	if (m_iControl) Control(tick);

	GameObject::Update(g, tick);
}

void PongBar::OnCollisionEnter(CollObject* other)
{
	if (other->GetName() == "pongball")
	{

	}
}
