#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	int speed;
protected:
	void MoveInput(DWORD tick);
public:
	Player();
	virtual ~Player();

	void SetSpeed(int speed) { this->speed = speed; }
	virtual void Update(Graphics* g, DWORD tick);
};

