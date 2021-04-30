#pragma once

#include "CollObject.h"

class PongBar : public CollObject
{
private:
	bool m_iControl;

private:
	void Control(DWORD tick);
	void PongBarProcess();

public:
	PongBar() : CollObject(), m_iControl(false) {}
	virtual ~PongBar() {}
	
	void SetLocalControl() { m_iControl = true; }

	void Init();
	void Update(Graphics* g, DWORD tick);

	void OnCollisionEnter(CollObject* other);
};

