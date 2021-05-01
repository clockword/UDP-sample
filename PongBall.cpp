#include "PongBall.h"

void PongBall::BounceByWall()
{
	int radius = GetCollider()->GetRadius();
	Point position = GetPosition();
	Vector2 velocity = GetVelocity();
	if (position.Y > 768 - radius)
	{
		SetMovedPosition(Point(position.X, 768 - radius));
		SetVelocity(Vector2::Reflection(velocity, Vector2::Down).GetNormalized() * m_speed);
	}
	else if (position.Y < 0 + radius)
	{
		SetMovedPosition(Point(position.X, 0 + radius));
		SetVelocity(Vector2::Reflection(velocity, Vector2::Up).GetNormalized() * m_speed);
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
	SetVelocity(Vector2::Rotate(Vector2::Up, rotation) * m_speed);
}

void PongBall::SetSpeedOrigin()
{
	SetSpeed(300.0f);
}

void PongBall::BounceOff(Vector2 mirror)
{
	Vector2 velocity = GetVelocity();

	SetSpeed(m_speed + 30.0f);
	if (m_speed >= GetMaxSpeed())
		m_speed = GetMaxSpeed();
	//Vector2 reflection = Vector2::Reflection(velocity, mirror).GetNormalized() * m_speed;
	float rotation = rand() % 2 ? rand() % 71 + 10 : rand() % 71 - 80;

	SetVelocity(Vector2::Rotate(mirror, rotation) * m_speed);
}

void PongBall::Init()
{
	CollObject::Init();
	SetSpeed(300.0f);
	SetMaxSpeed(1000.0f);
	SetFriction(0.0f);
}

void PongBall::Update(Graphics* g, DWORD tick)
{
	BounceByWall();
	GameObject::Update(g, tick);
}

void PongBall::OnCollisionEnter(CollObject* other)
{

}
