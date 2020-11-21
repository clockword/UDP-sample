#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

void Game::Load(std::string name)
{
	if (m_obj != nullptr)
	{
		delete[] m_obj;
		m_obj = nullptr;
	}

	FILE* fp = nullptr;

	std::string path = "./Resource/Level/" + name + ".txt";
	fopen_s(&fp, path.c_str(), "rt");

	int count;
	std::string* key;
	char ch[256];

	fscanf_s(fp, "%d", &count);
	key = new std::string[count];
	for (int i = 0; i < count; ++i)
	{
		fscanf(fp, "%s", ch);
		key[i] = ch;
	}

	fscanf_s(fp, "%d", &count);
	m_count = count;
	m_obj = new GameObject[count];
	int key_index, x, y;
	for (int i = 0; i < count; ++i)
	{
		fscanf_s(fp, "%d %d %d", &key_index, &x, &y);
		m_obj[i].SetFile(key[key_index]);
		m_obj[i].SetImage(ResourceManager::LoadImage_(key[key_index]));
		m_obj[i].SetLocation(x, y);
	}

	fscanf_s(fp, "%d %d %d", &key_index, &x, &y);
	m_player.SetFile(key[key_index]);
	m_player.SetImage(ResourceManager::LoadImage_(key[key_index]));
	m_player.SetLocation(x, y);

	delete[] key;

	fclose(fp);
}

Game::Game()
{
	m_obj = nullptr;
	m_count = 0;
}

Game::~Game()
{
	if (m_obj != nullptr)
		delete[] m_obj;
}

void Game::Init()
{
	Load("lvl_test");

	m_player.SetSpeed(5);
}

void Game::Update(Graphics* g, DWORD tick)
{
	for (int i = 0; i < m_count; ++i)
	{
		m_obj[i].Update(g, tick);
	}
	m_player.Update(g, tick);
}

void Game::Delete()
{
	ResourceManager::DeleteImages();
}
