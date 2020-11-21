#pragma once
#include "ResourceManager.h"
#include "Player.h"

class Game
{
private:
	Player m_player;
	GameObject* m_obj;
	int m_count;
protected:
	void Load(std::string name);
public:
	Game();
	virtual ~Game();

	void Init();
	void Update(Graphics* g, DWORD tick);
	void Delete();
};

