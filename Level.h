#pragma once
#include <string>
#include <map>

#include "Game.h"
#include "Player.h"

#include "packet.h"

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
		GAME_OUT,
		HOST_START,
		FIND_START,
	};

	struct _gamePong
	{
		enum class _thisType
		{
			Server,
			Client,
		};
		_thisType playerType;
		int serverScore;
		int clientScore;
		GameObject* control;
		GameObject* other;
		bool otherConnected;
		float timedelayed;
		float startCount;
	};

	union LevelVariables
	{
		_gamePong pong;
		LevelVariables() {}
	};
	LevelVariables m_variables;

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

	void (*LevelProcess)(Level* level, DWORD tick);

	void RecievePacket(LPPACKETHEADER packet);

private:
	static void ButtonProcess(void* ctx, int index);
};