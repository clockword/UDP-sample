#pragma once

#include "GameObject.h"
#include "Vector2.h"
#include "Collider.h"

class Collider;
class CollObject : public GameObject
{
private:
	Collider* m_collider;
	Vector2 m_acceleration;
	float m_friction;
	Vector2 m_velocity;
	float m_maxSpeed;
	float m_mass;
	
private:
	void PhysicsProcess(DWORD tick);

protected:
	virtual void Draw(Graphics* g);

	void SetAcceleration(Vector2 vec) { m_acceleration = vec; }
	void AddAcceleration(Vector2 vec) { m_acceleration += vec; }
	Vector2 GetAcceleration() { return m_acceleration; }
	void SetFriction(float friction) { m_friction = friction; }
	void AddFriction(float friction) { m_friction += friction; }
	float GetFriction() { return m_friction; }
	void SetVelocity(Vector2 vec) { m_velocity = vec; }
	Vector2 GetVelocity() { return m_velocity; }
	void SetMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
	void SetMass(float mass) { m_mass = mass; }
	Vector2 GetForce() { return m_acceleration * m_mass; }

public:
	CollObject() : GameObject(), m_collider(nullptr){}
	virtual ~CollObject();

	void SetCollider(std::string filename);
	Collider* GetCollider() { return m_collider; }

	virtual void FixedUpdate(DWORD tick);
	virtual void OnCollisionEnter(CollObject* other);
};

