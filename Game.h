#pragma once
#include <string>
#include <map>

#include "Player.h"
#include "Level.h"
#include "World.h"

#include "packet.h"

class Level;
class Game
{
private:
	SOCKADDR_IN m_otherAddr;
	SOCKET m_socket;
	std::string m_ip;
	unsigned short m_port;

	typedef std::map<std::string, Level*> Levels;
	Levels m_levels;
	Level* m_currentLevel;

	DWORD m_fixedFrame;
	DWORD m_fixedCount;

	bool m_run;

private:
	void AddLevel(std::string name);
	
	void err_quit(char* msg);

public:
	Game();
	virtual ~Game();

	Level* GetCurrentLevel() { return m_currentLevel; }
	void ChangeLevel(std::string name);

	bool Run() { return m_run; }
	void RunOff() { m_run = false; }

	void SetIp(std::string ip) { m_ip = ip; }
	std::string GetIp() { return m_ip; }
	void SetPortNumber(unsigned short port) { m_port = port; }
	short GetPortNumber() { return m_port; }
	void SetSocket(SOCKET sock) { m_socket = sock; }

	void FindGame();
	void HostGame();

	void Send(LPPACKETHEADER packet);
	void Recieve(const char buf[1024]);

	void Init();
	void Update(Graphics* g, DWORD tick);
	void Delete();
};

