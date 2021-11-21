#include "ftpch.h"

#include "Engine/States/Game.h"
#include "Engine/Random.h"
#include "App.h"

namespace Game {

	Game::Game()
	{
		m_ScreenWidth = Engine::Application::Get()->GetWindow()->GetWidth();
		m_ScreenHeight = Engine::Application::Get()->GetWindow()->GetHeight();
		
		InitMap();

		SetAndSavePoints(m_Points);

		{
			m_StarProps.Radius = sf::Vector2i(1, 3);
			m_StarProps.PositionX = sf::Vector2f(m_ScreenWidth, m_ScreenWidth * 2);
			m_StarProps.PositionY = sf::Vector2f(10, m_ScreenHeight - 10.0f);
			m_StarProps.SpeedRandomRangeX = sf::Vector2i(-250, -250);
			m_StarProps.SpeedRandomRangeY = sf::Vector2i(0, 0);
			m_StarProps.Time = sf::Vector2i(1, 5);
		}
	}

	Game::~Game()
	{
		delete m_Player;
	}

	// Engine loop functions

	void Game::OnUpdate(float ts)
	{
		if (m_State == GAMESTATE::PLAY)
		{
			OnUpdatePLAY(ts);
		}
		else if (m_State == GAMESTATE::PAUSE)
		{
			m_Player->SetVolume(0);

			m_PauseOverlay.OnUpdate(ts);
		}
	}

	void Game::OnEvent(sf::Event& e)
	{
		if (m_State == GAMESTATE::PLAY)
		{
			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					// pop this state fron the State mananger
					Quit();
				}
			}

			m_Player->OnEvent(e);
			m_UI.OnEvent(e);
		}
		else if (m_State == GAMESTATE::PAUSE)
		{
			m_PauseOverlay.OnEvent(e);
		}
	}

	void Game::OnRender(Engine::Graphics::Window* window)
	{
		m_StarGenerator.OnRender(window);

		for (auto& pillar : m_PillarsPool)
		{
			pillar.Render(window);
		}

		window->Render(m_TopFloor);
		window->Render(m_BotFloor);

		m_Player->Render(window);
		m_UI.OnRender(window);

		if (m_State == GAMESTATE::PAUSE)
		{
			m_PauseOverlay.OnRender(window);
		}

	}

	void Game::OnUpdatePLAY(float ts)
	{
		m_Player->OnUpdate(ts);

		m_UI.OnUpdate(ts);

		m_StarGenerator.OnUpdate(ts, m_StarProps);

		for (auto& pillar : m_PillarsPool)
		{
			pillar.OnUpdate(ts);
		}

		// Spawning pillars every time when they cross the map boundaries

		for (int i = 0; i <= MAX_AMOUNT_OF_PILLARS - 1; i += 2)
		{
			if (m_PillarsPool[i].GetPosition().x + m_PillarsPool[i].GetWidth() / 2 < 0.0f)
			{
				m_TempStartPlace = 0;

				for (int j = 0; j < MAX_AMOUNT_OF_PILLARS; j++)
				{
					if (m_PillarsPool[j].GetPosition().x > m_TempStartPlace)
						m_TempStartPlace = m_PillarsPool[j].GetPosition().x;
				}

				int t = m_TempStartPlace;
				SpawnPillars(m_PillarsPool[i], m_PillarsPool[i + 1], t);
			}

			// Check if Player has passed the pillar and count it if so

			CountPoints(i);
		}

		for (auto vertex : m_Player->GetVerticesCoordinates())
		{
			CollisionTest(vertex);
		}

		SetColors();
	}

	void Game::InitMap()
	{
		// Player

		m_Player = new Player();

		m_Player->m_SmokeProps.SpeedRandomRangeX = sf::Vector2i(-3, 3);
		m_Player->m_SmokeProps.SpeedRandomRangeY = sf::Vector2i(-3, 3);


		// UI stuff

		{
			m_UI.RegisterText("SCORE: ");
			m_UI.RegisterText("Points");

			m_UI.GetText("SCORE: ").setPosition(70, 46);
			m_UI.GetText("Points").setPosition(190, 46);

			m_Player->SetVitality(false);
		}
		
		// Minor units

		{
			m_TopFloor.setSize(sf::Vector2f(m_ScreenWidth, 400.0f));
			m_TopFloor.setOrigin(m_TopFloor.getSize().x / 2, m_TopFloor.getSize().y / 2);
			m_TopFloor.setPosition(m_ScreenWidth / 2, MAX_POSITION_OF_PILLAR + 25.0f);

			m_BotFloor.setSize(sf::Vector2f(m_ScreenWidth, 400.0f));
			m_BotFloor.setOrigin(m_BotFloor.getSize().x / 2, m_BotFloor.getSize().y / 2);
			m_BotFloor.setPosition(m_ScreenWidth / 2, MIN_POSITION_OF_PILLAR + 395.0f);

			InitPillars();
		}

	}

	void Game::InitPillars()
	{
		int startPlace = START_X_COORD_OF_PILLARS;

		m_PillarsPool.resize(MAX_AMOUNT_OF_PILLARS);

		for (int i = 0; i <= MAX_AMOUNT_OF_PILLARS - 1; i += 2)
		{
			SpawnPillars(m_PillarsPool[i], m_PillarsPool[i + 1], startPlace);
		}

	}

	void Game::SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& viewSizeX)
	{
		int x = Engine::Random::RangedRandom(4, 7);
		int y = Engine::Random::RangedRandom(2, 7);

		topPillar.SetPosition(sf::Vector2f(viewSizeX + DISTANCE_MULTIPLIER * x, MAX_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * y / 2)));
		topPillar.SetAsAddable(true);

		y = Engine::Random::RangedRandom(y + 2, y + 4);
		bottomPillar.SetPosition(sf::Vector2f(viewSizeX + DISTANCE_MULTIPLIER * x, MIN_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * y / 2)));

		viewSizeX += DISTANCE_MULTIPLIER * x;
	}

	void Game::CollisionTest(sf::Vector2f vector)
	{
		bool pillarCollision = false;
		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			if (m_PillarsPool[i].Contains(vector))
			{
				pillarCollision = true;
				break;
			}
		}

		bool wallCollision = m_BotFloor.getGlobalBounds().contains(vector) || m_TopFloor.getGlobalBounds().contains(vector);

		if (pillarCollision || wallCollision)
		{
			m_Player->SetVitality(false);
			SetAndSavePoints(m_Points);
			SwitchState();
		}
	}

	void Game::CountPoints(int i)
	{
		if (m_PillarsPool[i].GetPosition().x + m_PillarsPool[i].GetWidth() / 2 < m_Player->GetPosition().x - m_Player->GetSize().x)
		{
			if (m_PillarsPool[i].CanAddToPoints())
			{
				m_Points++;
			}

			m_PillarsPool[i].SetAsAddable(false);
		}

		std::string pointsText = std::to_string(m_Points);
		m_UI.GetText("Points").setString(pointsText);
	}

	// Changing colors of the Map dynamically

	void Game::SetColors()
	{
		for (auto& pillar : m_PillarsPool)
		{
			pillar.SetColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));
		}

		m_TopFloor.setFillColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));
		m_BotFloor.setFillColor(sf::Color(m_Color.R, m_Color.G, m_Color.B, 255));

		{
			if (m_Color.R > 254)
				m_Color.incrementR = -1;
			else if (m_Color.R < 1)
				m_Color.incrementR = 1;

			m_Color.R += m_Color.incrementR;

			if (m_Color.G > 254)
				m_Color.incrementG = -1;
			else if (m_Color.G < 1)
				m_Color.incrementG = 1;

			m_Color.G += m_Color.incrementG;

			if (m_Color.B > 254)
				m_Color.incrementB = -1;
			else if (m_Color.B < 1)
				m_Color.incrementB = 1;

			m_Color.B += m_Color.incrementB;
		}
	}

	// Set and Save High Points to the file 

	void Game::SetAndSavePoints(int point)
	{
		std::string line;
		std::string pointsText;

		// taking saved points fron the file

		std::ifstream in("res/points/points.fr"); 
		if (in.is_open())
		{
			std::getline(in, line);
			
			if (line != "")
			{
				m_HighPoints = std::stoi(line);
			}
		}
		in.close();

		// check if current points higher then the saved in the file one and save it if so

		std::ofstream out; 
		out.open("res/points/points.fr"); 
		if (out.is_open())
		{
			if (m_HighPoints > m_Points)
			{
				out << m_HighPoints;

				// save points as string
				pointsText = std::to_string(m_HighPoints);
			}
			else
			{
				out << m_Points;
				m_HighPoints = m_Points;

				// save points as string
				pointsText = std::to_string(m_Points);
			}
		}
		out.close();

		// set UI text that displaying high points
		m_PauseOverlay.GetUI().GetText("HIGH_SCORE").setString(pointsText);
	}

	void Game::Reset()
	{
		InitPillars();
		m_Player->Reset();
		m_Points = 0;
		m_StarGenerator.Reset();
	}

	// Switching state between PLAY and PAUSE states

	void Game::SwitchState()
	{
		m_State = (m_State == GAMESTATE::PAUSE) ? GAMESTATE::PLAY : m_State = GAMESTATE::PAUSE;
	}

	void Game::Quit()
	{
		m_isQuit = true;
	}

	void Game::SetActive()
	{
		m_isQuit = false;
	}

}