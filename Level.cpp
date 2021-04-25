#include "Level.h"
#include "Player.h"
#include "Button.h"
#include "TextBox.h"
#include "Text.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollObject.h"

Level::Level(std::string name)
{
	m_name = name;
	m_isCleared = false;
}

Level::~Level()
{
	std::map<int, GameObject*>::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		delete it->second;
	}
	m_obj.clear();
}

void Level::Init()
{
	Objects::iterator it = m_obj.begin();
	for (; it != m_obj.end(); it++)
	{
		it->second->Init();
	}

	if (m_name == "lvl_title")
	{
		static_cast<Button*>(m_obj[1])->RegisterButtonFunc(
			ButtonProcess, this, (int)ButtonWork::LVL_HOST);
		static_cast<Button*>(m_obj[1])->RegisterButtonFunc(
			ButtonProcess, this, (int)ButtonWork::LVL_FIND);
	}
	else if (m_name == "lvl_find")
	{

	}
	else if (m_name == "lvl_host")
	{

	}
	else if (m_name == "lvl_inGame")
	{

	}

	World::GetInstance()->Init();
}

void Level::Update(Graphics* g, DWORD tick)
{
	Objects::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		it->second->Update(g, tick);
	}
}

void Level::Load()
{
	UnLoad();

	FILE* fp = nullptr;

	std::string path = "./Resource/Level/" + m_name + ".txt";
	fp = fopen(path.c_str(), "rt");

	while (true)
	{
		int key, posX, posY;
		std::string name;
		std::string tag;

		char ch_name[255] = { 0, };
		char ch_tag[255] = { 0, };
		fscanf(fp, "%d %s %s %d %d", &key, ch_tag, ch_name, &posX, &posY);
		name = ch_name;
		tag = ch_tag;
		if (name == "End")
			break;
		std::string type = name.substr(0, 2);
		std::string img = name.substr(3);
		if (type == "bg")
		{
			m_obj[key] = new GameObject();
		}
		else if (type == "bt")
		{
			m_obj[key] = new Button();
			InputManager::GetInstance()->RegisterButton(static_cast<Button*>(m_obj[key]));
		}
		else if (type == "pl")
		{
			m_obj[key] = new Player();
		}
		else if (type == "co")
		{
			m_obj[key] = new CollObject();
			World::GetInstance()->RegisterCollObject(tag, static_cast<CollObject*>(m_obj[key]));
		}
		else if (type == "tb")
		{
			m_obj[key] = new TextBox();
			InputManager::GetInstance()->RegisterTextBox(static_cast<TextBox*>(m_obj[key]));
		}
		else if (type == "tx")
		{
			m_obj[key] = new Text();
		}

		m_obj[key]->SetFile(img);
		m_obj[key]->SetImage(ResourceManager::GetInstance()->LoadImage_(img));
		m_obj[key]->SetTag(tag);
		m_obj[key]->SetCollider(img);
		m_obj[key]->SetLocation(posX, posY);
	}

	fclose(fp);
}

void Level::UnLoad()
{
	World::GetInstance()->ClearRegistered();
	InputManager::GetInstance()->ClearRegistered();
	Objects::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		delete it->second;
	}
	m_obj.clear();
}

void Level::ButtonProcess(void* ctx, int index)
{
	Level* level = static_cast<Level*>(ctx);

	switch (index)
	{
	case (int)ButtonWork::LVL_TITLE:
	{
		level->GetThisGame()->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::LVL_HOST:
	{

	}break;
	case (int)ButtonWork::LVL_FIND:
	{
		
	}break;
	case (int)ButtonWork::LVL_INGAME:
	{

	}break;
	}
}