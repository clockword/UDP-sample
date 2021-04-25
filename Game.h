#pragma once
#include <string>
#include <map>

#include "Player.h"
#include "Level.h"
#include "World.h"

class Level;
class Game
{
private:
	typedef std::map<std::string, Level*> Levels;
	Levels m_levels;
	Level* m_currentLevel;

	DWORD m_targetFrame;
	DWORD m_fixedFrame;
	DWORD m_frameCount;
	DWORD m_fixedCount;

private:
	void AddLevel(std::string name);

public:
	Game();
	virtual ~Game();

	void ChangeLevel(std::string name);

	void Init();
	void Update(Graphics* g, DWORD tick);
	void Delete();
};

