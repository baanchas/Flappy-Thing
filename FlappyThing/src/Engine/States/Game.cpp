#include "ftpch.h"

#define _CRT_SECURE_NO_WARNINGS

#include "Engine/States/Game.h"
#include "Engine/Physics/Physics2D.h"
#include "Engine/Random.h"
#include "App.h"

namespace Game {

	Game::Game()
	{

		m_DefaultFont.loadFromFile("res/fonts/FastHand.ttf");
		
		m_ScoreText.setFont(m_DefaultFont);
		m_ScoreText.setString("SCORE: ");
		m_ScoreText.setCharacterSize(24);
		m_ScoreText.setStyle(sf::Text::Regular);
		m_ScoreText.setFillColor(sf::Color::Red);
		m_ScoreText.setPosition(10, 50);
		m_ScoreText.setOutlineColor(sf::Color::White);
		m_ScoreText.setOutlineThickness(2);

		m_PointsText.setFont(m_DefaultFont);
		m_PointsText.setCharacterSize(24);
		m_PointsText.setStyle(sf::Text::Regular);
		m_PointsText.setFillColor(sf::Color::Red);
		m_PointsText.setPosition(120, 50);
		m_PointsText.setOutlineColor(sf::Color::White);
		m_PointsText.setOutlineThickness(2);


		m_Player = new Player();

		m_Camera = new sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f));
		
		m_TopFloor.setSize(sf::Vector2f(1280.0f, 400.0f));
		m_TopFloor.setOrigin(m_TopFloor.getSize().x / 2, m_TopFloor.getSize().y / 2);
		m_TopFloor.setPosition(640.0f, -175.0f);

		m_BotFloor.setSize(sf::Vector2f(1280.0f, 400.0f));
		m_BotFloor.setOrigin(m_BotFloor.getSize().x / 2, m_BotFloor.getSize().y / 2);
		m_BotFloor.setPosition(640.0f, 895.0f);

		InitPillars();
	}


	Game::~Game()
	{
		delete m_Camera;
		delete m_Player;
	}

	void Game::OnUpdate(float ts)
	{
		//Engine::Application::Get()->SetWindowCamera(m_Camera);
		//m_Camera->setCenter(m_Player->GetPosition());
		m_Player->OnUpdate(ts);

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			m_Pillars[i].OnUpdate(ts);

			if (i % 2 == 0)
			{
				if (m_Pillars[i].GetPosition().x + m_Pillars[i].GetWidth() / 2 < m_Player->GetPosition().x - m_Player->GetSize().x)
				{
					if (m_Pillars[i].CanAddToPoints())
					{
						m_Points++;
						std::cout << m_Points << std::endl;
					}
					m_Pillars[i].SetAsAddable(false);

				}

				if (m_Pillars[i].GetPosition().x + m_Pillars[i].GetWidth() / 2 < 0.0f)
				{
					m_TempStartPlace = 0.0f;

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


		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			if (m_Pillars[i].Contains(m_Player->GetVerticesCoordinates()[0])
				|| m_Pillars[i].Contains(m_Player->GetVerticesCoordinates()[1])
				|| m_Pillars[i].Contains(m_Player->GetVerticesCoordinates()[2])
				|| m_Pillars[i].Contains(m_Player->GetVerticesCoordinates()[3]))
			{
				std::cout << "contains " << i << std::endl;
			}
		}

		std::string pointsText = std::to_string(m_Points);

		m_PointsText.setString(pointsText);
	}

	void Game::OnEvent(sf::Event& e)
	{
		m_Player->OnEvent(e);

		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				Quit();
			}
		}
	}

	void Game::OnRender(Engine::Graphics::Window* window)
	{
		m_Player->Render(window);
		for (size_t i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			m_Pillars[i].Render(window);
		}

		window->Render(m_TopFloor);
		window->Render(m_BotFloor);
		window->Render(m_ScoreText);
		window->Render(m_PointsText);
	}

	void Game::InitPillars()
	{
		int startPlace = START_X_COORD_OF_PILLARS;

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			Pillar pillar;
			m_Pillars.push_back(pillar);

			if (i % 2 == 1)
			{
				m_Pillars[i].SetRotation(180.0f);
			}
		}

		for (int i = 0; i < MAX_AMOUNT_OF_PILLARS - 1; i++)
		{
			if (i % 2 == 0)
			{
				SpawnPillars(m_Pillars[i], m_Pillars[i + 1], startPlace);
			}
		}
	}

	void Game::SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& startPlace)
	{
		int tempRandX = Engine::Random::RangedRandom(4, 10);
		int tempRandY = Engine::Random::RangedRandom(3, 7);
		topPillar.SetPosition(sf::Vector2f(startPlace + DISTANCE_MULTIPLIER * tempRandX, MAX_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * tempRandY / 2)));

		tempRandY = Engine::Random::RangedRandom(tempRandY + 2, tempRandY + 3);
		bottomPillar.SetPosition(sf::Vector2f(startPlace + DISTANCE_MULTIPLIER * tempRandX, MIN_POSITION_OF_PILLAR + (DISTANCE_MULTIPLIER * tempRandY / 2)));

		startPlace += DISTANCE_MULTIPLIER * tempRandX;

		topPillar.SetAsAddable(true);
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