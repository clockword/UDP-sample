#pragma once

#include "CollObject.h"
#include "packet.h"

class PongBar : public CollObject
{
private:
	bool m_iControl;

private:
	void Control(DWORD tick);

public:
	PongBar() : CollObject(), m_iControl(false) {}
	virtual ~PongBar() {}

	CHARMOVE GetPacket();
	
	void SetLocalControl() { m_iControl = true; }

	void Init();
	void Update(Graphics* g, DWORD tick);

	void OnCollisionEnter(CollObject* other);
};

