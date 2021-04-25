#pragma once
#include <string>
#include <map>

#include "Game.h"
#include "Player.h"

class Game;
class Level
{
private:
	typedef std::map<int, GameObject*> Objects;
	std::string m_name;
	Objects m_obj;
	bool m_isCleared;

	Game* m_game;

private:
	enum class ButtonWork
	{
		LVL_TITLE,
		LVL_HOST,
		LVL_FIND,
		LVL_INGAME,
	};

public:
	bool GetIsClear()const { return m_isCleared; }
	std::string GetName()const { return m_name; }

public:
	Level(std::string name);
	virtual ~Level();

	void Init();
	void Update(Graphics* g, DWORD tick);

	void Load();
	void UnLoad();

	void SetThisGame(Game* game) { m_game = game; }
	Game* GetThisGame() { return m_game; }

private:
	static void ButtonProcess(void* ctx, int index);
};