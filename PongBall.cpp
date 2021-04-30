#include "PongBall.h"

void PongBall::BounceOff()
{
	int radius = GetCollider()->GetRadius();
	Point position = GetPosition();
	Vector2 velocity = GetVelocity();
	if (position.Y > 768 - radius)
	{
		SetVelocity(Vector2::Reflection(velocity, Vector2::Down));
	}
	else if (position.Y < 0 + radius)
	{
		SetVelocity(Vector2::Reflection(velocity, Vector2::Up));
	}
}

void PongBall::StartShoot()
{
	float rotation;
	if (rand() % 2)
	{
		rotation = rand() % 71 + 10;
		if (rand() % 2) rotation += 90.0f;
	}
	else
	{
		rotation = rand() % 71 - 80;
		if (rand() % 2) rotation -= 90.0f;
	}
	SetVelocity(Vector2::Rotate(Vector2::Up, rotation) * 300.0f);
}

void PongBall::Init()
{
	CollObject::Init();
	SetMaxSpeed(1000.0f);
	SetFriction(0.0f);
}

void PongBall::Update(Graphics* g, DWORD tick)
{
	BounceOff();
	GameObject::Update(g, tick);
}

void PongBall::OnCollisionEnter(CollObject* other)
{

}
