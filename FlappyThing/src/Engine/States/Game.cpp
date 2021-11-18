#include "ftpch.h"

#include "Engine/States/Game.h"
#include "Engine/Physics/Physics2D.h"
#include "Engine/Random.h"
#include "App.h"

namespace Game {

	Game::Game()
	{
		m_ScreenWidth = Engine::Application::Get()->GetWindow()->GetWidth();
		m_ScreenHeight = Engine::Application::Get()->GetWindow()->GetHeight();

		InitMap();

		m_UI.RegisterText("SCORE: ");
		m_UI.RegisterText("Points");

	}

	Game::~Game()
	{
		delete m_Player;
		delete m_Camera;
	}

	void Game::OnUpdate(float ts)
	{
		if (m_State == GAMESTATE::PLAY)
		{
			m_Player->OnUpdate(ts);

			for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
			{
				m_Pillars[i].OnUpdate(ts);

				if (i % 2 == 0)
				{
					CountPoints(i);

					if (m_Pillars[i].GetPosition().x + m_Pillars[i].GetWidth() / 2 < 0.0f)
					{
						m_TempStartPlace = 0;

						for (int j = 0; j < MAX_AMOUNT_OF_PILLARS; j++)
						{
							if (m_Pillars[j].GetPosition().x > m_TempStartPlace)
								m_TempStartPlace = m_Pillars[j].GetPosition().x;
						}

						int t = m_TempStartPlace;

						SpawnPillars(m_Pillars[i], m_Pillars[i + 1], t);
					}
				}
			}

			CollisionTest();

			SetColors();

			m_UI.OnUpdate(ts);

		}
		else if (m_State == GAMESTATE::PAUSE)
		{
			m_PauseOverlay.OnUpdate(ts);

			if (!m_Player->IsAlive())
			{
				m_PauseOverlay.GetUI().GetButton("RESUME").SetUnActive();
			}
		}
	}

	void Game::OnEvent(sf::Event& e)
	{
		if (m_State == GAMESTATE::PLAY)
		{
			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Escape && m_Player->IsAlive())
				{
					SwitchState();
				}
			}

			m_Player->OnEvent(e);

			m_UI.OnEvent(e);
		}
		else if (m_State == GAMESTATE::PAUSE)
		{
			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Escape && m_Player->IsAlive())
				{
					SwitchState();
				}
			}

			m_PauseOverlay.OnEvent(e);

			if (m_PauseOverlay.GetUI().GetButton("RESUME").IsClicked())
			{
				SwitchState();
			}

			if (m_PauseOverlay.GetUI().GetButton("NEW GAME").IsClicked())
			{
				Reset();
				SwitchState();
			}

			if (m_PauseOverlay.GetUI().GetButton("EXIT TO MENU").IsClicked())
			{
				Quit();
			}
		}
	}

	void Game::OnRender(Engine::Graphics::Window* window)
	{

		for (size_t i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			m_Pillars[i].Render(window);
		}

		window->Render(m_TopFloor);
		window->Render(m_BotFloor);

		m_UI.OnRender(window);
		m_Player->Render(window);

		m_PauseOverlay.OnRender(window);
	}

	void Game::InitMap()
	{
		m_Camera = new sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(m_ScreenWidth, m_ScreenHeight));

		m_Camera->setCenter(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));

		m_Player = new Player();

		float floorsHeight = 400.0f;

		m_TopFloor.setSize(sf::Vector2f(m_ScreenWidth, 400.0f));
		m_TopFloor.setOrigin(m_TopFloor.getSize().x / 2, m_TopFloor.getSize().y / 2);
		m_TopFloor.setPosition(m_ScreenWidth / 2, MAX_POSITION_OF_PILLAR + 25.0f);

		m_BotFloor.setSize(sf::Vector2f(m_ScreenWidth, 400.0f));
		m_BotFloor.setOrigin(m_BotFloor.getSize().x / 2, m_BotFloor.getSize().y / 2);
		m_BotFloor.setPosition(m_ScreenWidth / 2, MIN_POSITION_OF_PILLAR + 395.0f);

		InitPillars();
	}

	void Game::InitPillars()
	{
		int startPlace = START_X_COORD_OF_PILLARS;

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			Pillar pillar;
			m_Pillars.push_back(pillar);
		}

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS - 1; i++)
		{
			if (i % 2 == 0)
			{
				SpawnPillars(m_Pillars[i], m_Pillars[i + 1], startPlace);
			}
		}
	}

	void Game::SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& viewSizeX)
	{
		int x = Engine::Random::RangedRandom(4, 8);
		int y = Engine::Random::RangedRandom(2, 7);
		topPillar.SetPosition(sf::Vector2f(viewSizeX + DISTANCE_MULTIPLIER * x, MAX_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * y / 2)));

		y = Engine::Random::RangedRandom(y + 2, y + 4);
		bottomPillar.SetPosition(sf::Vector2f(viewSizeX + DISTANCE_MULTIPLIER * x, MIN_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * y / 2)));

		viewSizeX += DISTANCE_MULTIPLIER * x;

		topPillar.SetAsAddable(true);
	}

	void Game::CollisionTest()
	{
		bool collision = false;

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			for (auto element : m_Player->GetVerticesCoordinates())
			{
				if (m_Pillars[i].Contains(element) || m_BotFloor.getGlobalBounds().contains(element) || m_TopFloor.getGlobalBounds().contains(element))
				{
					collision = true;
					break;
				}
			}

			if (collision)
			{
				m_Player->SetVitaliy(false);
				SwitchState();
				break;
			}
		}
		
	}

	void Game::CountPoints(int i)
	{
		if (m_Pillars[i].GetPosition().x + m_Pillars[i].GetWidth() / 2 < m_Player->GetPosition().x - m_Player->GetSize().x)
		{
			if (m_Pillars[i].CanAddToPoints())
			{
				m_Points++;
			}
			m_Pillars[i].SetAsAddable(false);
		}

		std::string pointsText = std::to_string(m_Points);
		m_UI.GetText("Points").setString(pointsText);

		m_UI.GetText("SCORE: ").setPosition(60, m_Camera->getCenter().y - m_ScreenHeight / 2 + 46);
		m_UI.GetText("Points").setPosition(160, m_Camera->getCenter().y - m_ScreenHeight / 2 + 48);
	}

	void Game::SetColors()
	{
		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			m_Pillars[i].SetColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));
		}

		m_TopFloor.setFillColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));
		m_BotFloor.setFillColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));

		if (m_Color.R > 254)
		{
			m_Color.incrementR = -1;
		}
		else if (m_Color.R < 1)
		{
			m_Color.incrementR = 1;
		}
		m_Color.R += m_Color.incrementR;

		if (m_Color.G > 254)
		{
			m_Color.incrementG = -1;
		}
		else if (m_Color.G < 1)
		{
			m_Color.incrementG = 1;
		}

		m_Color.G += m_Color.incrementG;

		if (m_Color.B > 254)
		{
			m_Color.incrementB = -1;
		}
		else if (m_Color.B < 1)
		{
			m_Color.incrementB = 1;
		}

		m_Color.B += m_Color.incrementB;
	}

	void Game::Reset()
	{
		InitPillars();
		m_Player->Reset(); 
		m_PauseOverlay.GetUI().GetButton("RESUME").SetActive();
		m_Points = 0;
	}

	void Game::SwitchState()
	{
		m_PauseOverlay.SwitchState();

		if (m_State == GAMESTATE::PAUSE)
		{
			m_State = GAMESTATE::PLAY;
		}
		else if (m_State == GAMESTATE::PLAY)
		{
			m_State = GAMESTATE::PAUSE;
		}

	}

	void Game::Quit()
	{
		m_isQuit = true;
	}

	void Game::SetAvtive()
	{
		m_isQuit = false;
	}

}