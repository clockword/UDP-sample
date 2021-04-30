#include "PongBar.h"

void PongBar::Control(DWORD tick)
{
	BYTE key[256];

	::GetKeyboardState(key);

	if (key[VK_UP] & 0x80)
	{
		if (GetVelocity().y > 0) SetVelocity(Vector2::Zero);
		SetAcceleration(Vector2::Up * 1000.0f);
	}
	else if (key[VK_DOWN] & 0x80)
	{
		if (GetVelocity().y < 0) SetVelocity(Vector2::Zero);
		SetAcceleration(Vector2::Down * 1000.0f);
	}
	else
	{
		SetAcceleration(Vector2::Zero);
	}
}

void PongBar::PongBarProcess()
{
	Point position = GetPosition();
	if (position.Y > 718)
	{
		SetPosition(position.X, 718);
		SetVelocity(-GetVelocity());
	}
	else if(position.Y < 50)
	{
		SetPosition(position.X, 50);
		SetVelocity(-GetVelocity());
	}
}

void PongBar::Init()
{
	CollObject::Init();
	SetMaxSpeed(100.0f);
	SetFriction(1.0f);
}

void PongBar::Update(Graphics* g, DWORD tick)
{
	if (m_iControl) Control(tick);
	PongBarProcess();
	GameObject::Update(g, tick);
}

void PongBar::OnCollisionEnter(CollObject* other)
{
	if (!m_iControl) return;

	if (other->GetName() == "pongball")
	{

	}
}
