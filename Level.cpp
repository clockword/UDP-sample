#include "Level.h"
#include "Player.h"
#include "Button.h"
#include "TextBox.h"
#include "Text.h"
#include "PongBar.h"
#include "PongBall.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollObject.h"

Level::Level(std::string name)
{
	m_name = name;
	m_isCleared = false;
	LevelProcess = nullptr;
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

		host_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::HOST_START);
		find_button->RegisterButtonFunc(ButtonProcess, this, (int)ButtonWork::FIND_START);
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
		auto server_score = static_cast<Text*>(m_obj[1]);
		auto client_score = static_cast<Text*>(m_obj[2]);
		auto count = static_cast<Text*>(m_obj[6]);
		auto ball = static_cast<PongBall*>(m_obj[5]);

		std::string font = "Impact";

		server_score->SetFont(font);
		server_score->SetTextColor(Color::White);
		server_score->SetFontSize(72);
		m_variables.pong.serverScore = 0;

		client_score->SetFont(font);
		client_score->SetTextColor(Color::White);
		client_score->SetFontSize(72);
		m_variables.pong.clientScore = 0;

		count->SetFont(font);
		count->SetTextColor(Color::Red);
		count->SetFontSize(96);
		m_variables.pong.startCount = 3.99f;

		m_variables.pong.otherConnected = false;
		m_variables.pong.timedelayed = 0.0f;

		count->SetActive(false);
		ball->SetActive(false);

		LevelProcess = [](Level* level, DWORD tick) -> void
		{
			auto server_score = static_cast<Text*>(level->m_obj[1]);
			auto client_score = static_cast<Text*>(level->m_obj[2]);
			auto count = static_cast<Text*>(level->m_obj[6]);
			auto ball = static_cast<PongBall*>(level->m_obj[5]);

			if (level->m_variables.pong.otherConnected)
			{
				PongBar* pongbar = static_cast<PongBar*>(level->m_variables.pong.control);

				server_score->SetText(std::to_string(level->m_variables.pong.serverScore));
				client_score->SetText(std::to_string(level->m_variables.pong.clientScore));

				CHARMOVE move;

				if (level->m_variables.pong.startCount > 0.0f)
				{
					if (level->m_variables.pong.playerType == _gamePong::_thisType::Server)
					{
						level->m_variables.pong.startCount -= tick * 0.001f;
						move.count = level->m_variables.pong.startCount;
						if (level->m_variables.pong.startCount <= 0.0f)
						{
							count->SetActive(false);
							ball->SetActive(true);
							ball->StartShoot();
						}
					}
					count->SetText(std::to_string((int)floor(level->m_variables.pong.startCount)));
				}

				level->m_variables.pong.timedelayed += tick * 0.001f;
				if (level->m_variables.pong.timedelayed >= 0.02f)
				{
					level->m_variables.pong.timedelayed = 0.0f;
					move.curX = pongbar->GetPosition().X;
					move.curY = pongbar->GetPosition().Y;
					move.ballX = ball->GetPosition().X;
					move.ballY = ball->GetPosition().Y;
					level->GetThisGame()->Send(&move);
				}

				if (ball->GetPosition().X < 0.0f)
				{
					level->m_variables.pong.clientScore += 1;
					level->m_variables.pong.startCount = 3.99f;
					count->SetActive(true);
					ball->SetActive(false);
					ball->SetMovedPosition(Point(512, 384));
				}
				else if (ball->GetPosition().X > 1024.0f)
				{
					level->m_variables.pong.serverScore += 1;
					level->m_variables.pong.startCount = 3.99f;
					count->SetActive(true);
					ball->SetActive(false);
					ball->SetMovedPosition(Point(512, 384));
				}
			}
			else
			{
				if (level->m_variables.pong.playerType == _gamePong::_thisType::Server)
				{
					server_score->SetText("Ready");
					client_score->SetText("Not Ready");
				}
				else if (level->m_variables.pong.playerType == _gamePong::_thisType::Client)
				{
					server_score->SetText("Not Ready");
					client_score->SetText("Ready");
				}

				LOGIN packet;
				packet.active = true;
				level->GetThisGame()->Send(&packet);
			}
		};
	}

	World::GetInstance()->Init();
}

void Level::Update(Graphics* g, DWORD tick)
{
	if (LevelProcess != nullptr) LevelProcess(this, tick);
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
		else if (type == "pb")
		{
			m_obj[key] = new PongBar();
			World::GetInstance()->RegisterCollObject(tag, static_cast<PongBar*>(m_obj[key]));
		}
		else if (type == "bl")
		{
			m_obj[key] = new PongBall();
			World::GetInstance()->RegisterCollObject(tag, static_cast<PongBall*>(m_obj[key]));
		}

		m_obj[key]->SetFile(img);
		m_obj[key]->SetImage(ResourceManager::GetInstance()->LoadImage_(img));
		m_obj[key]->SetTag(tag);
		m_obj[key]->SetName(name);
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

void Level::RecievePacket(LPPACKETHEADER packet)
{
	switch (packet->id)
	{
	case PKT_CHARMOVE:
	{
		LPCHARMOVE data = static_cast<LPCHARMOVE>(packet);

		if(m_name == "lvl_ingame")
		{
			PongBar* other = static_cast<PongBar*>(m_variables.pong.other);
			PongBall* ball = static_cast<PongBall*>(m_obj[5]);

			if (m_variables.pong.playerType == _gamePong::_thisType::Client)
			{
				m_variables.pong.startCount = data->count;
				if (data->count <= 0.0f)
				{
					auto startCount = m_obj[6];
					
					startCount->SetActive(false);
					ball->SetActive(true);
				}
				ball->SetMovedPosition(Point(data->ballX, data->ballY));
			}

			other->SetMovedPosition(Point(data->curX, data->curY));
		}
		
	}break;
	case PKT_LOGIN:
	{
		LPLOGIN data = static_cast<LPLOGIN>(packet);

		if (m_name == "lvl_ingame")
		{
			if (!m_variables.pong.otherConnected)
			{
				auto count = m_obj[6];
				count->SetActive(true);

				LOGIN packet;
				packet.active = true;
				m_game->Send(&packet);
			}

			m_variables.pong.otherConnected = data->active;
		}
	}break;
	}
}

void Level::ButtonProcess(void* ctx, int index)
{
	Level* level = static_cast<Level*>(ctx);
	Game* game = level->GetThisGame();

	switch (index)
	{
	case (int)ButtonWork::LVL_TITLE:
	{
		game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::LVL_HOST:
	{
		game->ChangeLevel("lvl_host");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::LVL_FIND:
	{
		game->ChangeLevel("lvl_find");
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::GAME_OUT:
	{
		level->UnLoad();
		game->RunOff();
		InputManager::GetInstance()->ShockOff();
	}break;
	case (int)ButtonWork::HOST_START:
	{
		game->HostGame();
		game->ChangeLevel("lvl_ingame");
		InputManager::GetInstance()->ShockOff();

		PongBar* pongbar = static_cast<PongBar*>(game->GetCurrentLevel()->m_obj[3]);
		game->GetCurrentLevel()->m_variables.pong.control = pongbar;
		game->GetCurrentLevel()->m_variables.pong.other = game->GetCurrentLevel()->m_obj[4];
		pongbar->SetLocalControl();
		game->GetCurrentLevel()->m_variables.pong.playerType = _gamePong::_thisType::Server;
	}break;
	case (int)ButtonWork::FIND_START:
	{
		game->FindGame();
		game->ChangeLevel("lvl_ingame");
		InputManager::GetInstance()->ShockOff();

		PongBar* pongbar = static_cast<PongBar*>(game->GetCurrentLevel()->m_obj[4]);
		game->GetCurrentLevel()->m_variables.pong.control = pongbar;
		game->GetCurrentLevel()->m_variables.pong.other = game->GetCurrentLevel()->m_obj[3];
		pongbar->SetLocalControl();
		game->GetCurrentLevel()->m_variables.pong.playerType = _gamePong::_thisType::Client;
	}break;
	}
}