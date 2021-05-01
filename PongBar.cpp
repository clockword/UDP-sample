#include "PongBar.h"
#include "PongBall.h"

void PongBar::Control(DWORD tick)
{
	BYTE key[256];

	::GetKeyboardState(key);

	if (m_iControl)
	{
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

void PongBar::FixedUpdate(DWORD tick)
{
	CollObject::FixedUpdate(tick);
}

void PongBar::OnCollisionEnter(CollObject* other)
{
	if (!m_iServer) return;

	if (other->GetName() == "pongball")
	{
		PongBall* ball = static_cast<PongBall*>(other);
		Point barpos = GetPosition();
		Point ballpos = other->GetPosition();
		float width = GetCollider()->GetSize().Width;
		float radius = ball->GetCollider()->GetRadius();

		ball->SetMovedPosition(Point(barpos.X < ballpos.X ? 
			barpos.X + width * 0.5f + radius : barpos.X - width * 0.5f - radius, ballpos.Y));
		ball->BounceOff(barpos.X < ballpos.X ? Vector2::Right : Vector2::Left);
	}
}
