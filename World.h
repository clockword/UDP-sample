#pragma once

#include <map>
#include <vector>
#include <string>
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

#include "CollObject.h"

class World
{
private:
	typedef std::vector<CollObject*> CollObjectArr;
	typedef std::map<std::string, CollObjectArr> CollObjectMap;
	CollObjectMap m_collObjects;

private:
	World() {}

	World(World&);
	World& operator=(World&);
public:
	static World* GetInstance();

	void Init();
	void FixedUpdate(DWORD tick);

	void RegisterCollObject(std::string tag, CollObject* object);
	void ClearRegistered();
};

