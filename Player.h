#pragma once
#include "CollObject.h"

class Player : public CollObject
{
private:
	enum class ANIKIND
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

protected:
	void MoveInput(DWORD tick);

public:
	Player() : CollObject() {}
	virtual ~Player() {}
	virtual void Init();
	virtual void Update(Graphics* g, DWORD tick);
};

