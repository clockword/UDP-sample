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

Game::Game()
{
	m_currentLevel = nullptr;

	m_targetFrame = 0;
	m_fixedFrame = 0;
	m_frameCount = 0;
	m_fixedCount = 0;
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
void Game::Init()
{
	m_targetFrame = 15;
	m_fixedFrame = 50;

	AddLevel("lvl_title");

	ChangeLevel("lvl_title");
}

void Game::Update(Graphics* g, DWORD tick)
{
	m_frameCount += tick;
	m_fixedCount += tick;
	if (m_frameCount >= m_targetFrame)
	{
		m_currentLevel->Update(g, m_frameCount);
		m_frameCount = 0;
	}
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
