#pragma once

#include "CollObject.h"

class PongBall : public CollObject
{
private:
	float m_speed;

private:
	void BounceByWall();
	void SetSpeed(float speed) { m_speed = speed; }

public:
	void StartShoot();
	void SetSpeedOrigin();

	void BounceOff(Vector2 mirror);

	void Init();
	void Update(Graphics* g, DWORD tick);
	void OnCollisionEnter(CollObject* other);
};

