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
	SOCKADDR_IN m_otherAddr;
	SOCKET m_socket;
	std::string m_ip;

	typedef std::map<std::string, Level*> Levels;
	Levels m_levels;
	Level* m_currentLevel;

	DWORD m_fixedFrame;
	DWORD m_fixedCount;

	bool m_run;

private:
	void AddLevel(std::string name);
	
	void err_quit(char* msg);

private:
	struct DATA
	{

	};

public:
	Game();
	virtual ~Game();

	void ChangeLevel(std::string name);

	bool Run() { return m_run; }
	void RunOff() { m_run = false; }

	void SetIp(std::string ip) { m_ip = ip; }
	void SetSocket(SOCKET sock) { m_socket = sock; }

	void FindGame();
	void HostGame();

	void Send();
	void Recieve(char buf[1024]);

	void Init();
	void Update(Graphics* g, DWORD tick);
	void Delete();
};

