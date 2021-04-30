#pragma once

#include "CollObject.h"

class PongBall : public CollObject
{
private:
	void BounceOff();

public:
	void StartShoot();

	void Init();
	void Update(Graphics* g, DWORD tick);
	void OnCollisionEnter(CollObject* other);
};

