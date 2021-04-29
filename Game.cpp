#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <iostream>

#include "ResourceManager.h"

void Game::AddLevel(std::string name)
{
	if (m_levels.find(name) == m_levels.end())
	{
		m_levels[name] = new Level(name);
		m_levels[name]->SetThisGame(this);
	}
}

void Game::err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

Game::Game()
{
	m_currentLevel = nullptr;

	m_fixedFrame = 0;
	m_fixedCount = 0;

	m_run = true;

	m_socket = INVALID_SOCKET;
}

Game::~Game()
{
	Levels::iterator it = m_levels.begin();
	for (; it != m_levels.end(); it++)
	{
		delete it->second;
	}
	m_levels.clear();
	m_currentLevel = nullptr;
}

void Game::ChangeLevel(std::string name)
{
	if (m_currentLevel != nullptr)
	{
		m_currentLevel->UnLoad();
	}
	m_currentLevel = m_levels[name];
	m_currentLevel->Load();
	m_currentLevel->Init();
}

void Game::FindGame()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = bind(m_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		closesocket(m_socket);
		err_quit("bind()");
	}

	ZeroMemory(&m_otherAddr, sizeof(m_otherAddr));
	m_otherAddr.sin_family = AF_INET;
	m_otherAddr.sin_port = htons(9000);
	m_otherAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
}

void Game::HostGame()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = bind(m_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		closesocket(m_socket);
		err_quit("bind()");
	}

	ZeroMemory(&m_otherAddr, sizeof(m_otherAddr));
	m_otherAddr.sin_family = AF_INET;
	m_otherAddr.sin_port = htons(9001);
	m_otherAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
}

void Game::Send()
{
	DATA data;

	int retval;
	int size = sizeof(DATA);
	retval = sendto(m_socket, (const char*)&data, size, 0, (SOCKADDR*)&m_otherAddr, sizeof(m_otherAddr));
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
		}
	}
}

void Game::Recieve(char buf[1024])
{
	DATA* data = (DATA*)buf;

}

void Game::Init()
{
	m_fixedFrame = 15;

	AddLevel("lvl_title");
	AddLevel("lvl_host");
	AddLevel("lvl_find");
	AddLevel("lvl_ingame");

	ChangeLevel("lvl_ingame");
}

void Game::Update(Graphics* g, DWORD tick)
{
	m_fixedCount += tick;
	m_currentLevel->Update(g, tick);
	if (m_fixedCount >= m_fixedFrame)
	{
		World::GetInstance()->FixedUpdate(m_fixedCount);
		m_fixedCount = 0;
	}
}

void Game::Delete()
{
	ResourceManager::GetInstance()->DeleteImages();
}