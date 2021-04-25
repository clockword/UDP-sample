#include "CollObject.h"

void CollObject::PhysicsProcess(DWORD tick)
{
	float deltatime = tick * 0.001f;
	Vector2 friction = m_velocity.GetReverse().GetNormalized() * m_friction * deltatime;
	m_velocity += m_acceleration * deltatime;
	if (m_velocity.GetMagnitude() > friction.GetMagnitude())
		m_velocity += friction;
	else
		m_velocity = Vector2::Zero();
	if (m_velocity.GetMagnitude() > m_maxSpeed)
		m_velocity = m_velocity.GetNormalized() * m_maxSpeed;}

void CollObject::Draw(Graphics* g)
{
	GameObject::Draw(g);
	if (m_collider != nullptr)
	{
		m_collider->Draw(g);
	}
}

CollObject::~CollObject()
{
	if (m_collider != nullptr)
		delete m_collider;
}

void CollObject::SetCollider(std::string filename)
{
	FILE* file = nullptr;

	std::string path = "./Resource/Collider/" + filename + ".txt";

	fopen_s(&file, path.c_str(), "rt");

	char type = NULL;
	fscanf_s(file, "%c", &type);
	switch (type)
	{
	case 'R':
	{
		int locX, locY, sizeW, sizeH;
		fscanf_s(file, "%d %d %d %d", &locX, &locY, &sizeW, &sizeH);
		m_collider = new ColliderRect(Size(sizeW, sizeH));
		m_collider->SetLocalPosition(Point(locX, locY));
	}break;
	case 'C':
	{
		int locX, locY, rad;
		fscanf_s(file, "%d %d %d", &locX, &locY, &rad);
		m_collider = new ColliderCircle(rad);
		m_collider->SetLocalPosition(Point(locX, locY));
	}break;
	}

	m_collider->SetThisCollObject(this);
	m_collider->SetPosition(GetPosition());

	fclose(file);
}

void CollObject::FixedUpdate(DWORD tick)
{
	PhysicsProcess(tick);
}

void CollObject::OnCollisionEnter(CollObject* other)
{
	
}
