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
		auto title_text = static_cast<Text*>(m_obj[4]);
		auto host_button = static_cast<Button*>(m_obj[1]);
		auto find_button = static_cast<Button*>(m_obj[2]);
		auto out_button = static_cast<Button*>(m_obj[3]);

		std::string font = "Comic Sans MS";

		host_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::LVL_HOST);
		find_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::LVL_FIND);
		out_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::GAME_OUT);

		title_text->SetText("Test Multiplayer");
		title_text->SetFont(font);

		host_button->SetText("Host Game");
		host_button->SetFont(font);
		host_button->SetSize(2.0f, 1.0f);

		find_button->SetText("Find Game");
		find_button->SetFont(font);
		find_button->SetSize(2.0f, 1.0f);

		out_button->SetText("Quit Game");
		out_button->SetFont(font);
		out_button->SetSize(2.0f, 1.0f);
	}
	else if (m_name == "lvl_host")
	{
		auto title_text = static_cast<Text*>(m_obj[4]);
		auto title_button = static_cast<Button*>(m_obj[1]);
		auto port_textbox = static_cast<TextBox*>(m_obj[2]);
		auto host_button = static_cast<Button*>(m_obj[3]);

		std::string font = "Comic Sans MS";

		title_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::LVL_TITLE);
		host_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::HOST_START);

		title_text->SetText("Host Game");
		title_text->SetFont(font);

		title_button->SetText("Back");
		title_button->SetFont(font);

		port_textbox->SetText("enter portnumber");
		port_textbox->SetFont(font);
		port_textbox->SetSize(3.0f, 1.0f);

		host_button->SetText("Start");
		host_button->SetFont(font);
	}
	else if (m_name == "lvl_find")
	{
		auto title_text = static_cast<Text*>(m_obj[5]);
		auto title_button = static_cast<Button*>(m_obj[1]);
		auto ip_textbox = static_cast<TextBox*>(m_obj[2]);
		auto port_textbox = static_cast<TextBox*>(m_obj[3]);
		auto find_button = static_cast<Button*>(m_obj[4]);

		std::string font = "Comic Sans MS";

		title_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::LVL_TITLE);
		find_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::FIND_START);

		title_text->SetText("Find Game");
		title_text->SetFont(font);

		title_button->SetText("Back");
		title_button->SetFont(font);

		ip_textbox->SetText("enter ip");
		ip_textbox->SetFont(font);
		ip_textbox->SetSize(3.0f, 1.0f);

		port_textbox->SetText("enter portnumber");
		port_textbox->SetFont(font);
		port_textbox->SetSize(3.0f, 1.0f);

		find_button->SetText("Start");
		find_button->SetFont(font);
	}
	else if (m_name == "lvl_ingame")
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
	LevelProcess(tick);
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
			World::GetInstance()->RegisterCollObject(tag, static_cast<CollObject*>(m_obj[key]));
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
		m_obj[key]->SetPosition(posX, posY);
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

void Level::LevelProcess(DWORD tick)
{
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
		level->GetThisGame()->ChangeLevel("lvl_host");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::LVL_FIND:
	{
		level->GetThisGame()->ChangeLevel("lvl_find");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::LVL_INGAME:
	{

	}break;
	case (int)ButtonWork::GAME_OUT:
	{
		level->UnLoad();
		level->GetThisGame()->RunOff();
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::HOST_START:
	{
		level->GetThisGame()->HostGame();
		level->GetThisGame()->ChangeLevel("lvl_ingame");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::FIND_START:
	{
		level->GetThisGame()->FindGame();
		level->GetThisGame()->ChangeLevel("lvl_ingame");
		InputManager::GetInstance()->ShockOff();
	}break;
	}
}