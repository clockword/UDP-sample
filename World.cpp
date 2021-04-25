#include "World.h"

World* World::GetInstance()
{
	static World instance;

	return &instance;
}

void World::Init()
{
}

void World::FixedUpdate(DWORD tick)
{
	CollObjectMap::iterator it = m_collObjects.begin();
	for(;it != m_collObjects.end(); it++)
	{ 
		CollObjectArr arr = it->second;
		std::string tag = it->first;
		CollObjectArr others;

		for each (CollObject* object in arr)
		{
			object->FixedUpdate(tick);

			for each (CollObject* other in others)
			{

			}
		}
	}
}

void World::RegisterCollObject(std::string tag, CollObject* object)
{
	m_collObjects[tag].push_back(object);
}

void World::ClearRegistered()
{
	CollObjectMap::iterator it = m_collObjects.begin();
	for (;it != m_collObjects.end(); it++)
	{
		it->second.clear();
	}
	m_collObjects.clear();
}
