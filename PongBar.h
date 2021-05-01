#pragma once

#include "CollObject.h"

class PongBar : public CollObject
{
private:
	bool m_iControl;
	bool m_iServer;

private:
	void Control(DWORD tick);
	void PongBarProcess();

public:
	PongBar() : CollObject(), m_iControl(false), m_iServer(false) {}
	virtual ~PongBar() {}
	
	void SetLocalControl() { m_iControl = true; }
	void SetServerControl() { m_iServer = true; }

	void Init();
	void Update(Graphics* g, DWORD tick);

	void FixedUpdate(DWORD tick);
	void OnCollisionEnter(CollObject* other);
};

