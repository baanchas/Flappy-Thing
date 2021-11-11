#include "ftpch.h"
#include "Engine/States/Game.h"
#include "Engine/Physics/Physics2D.h"
#include "Engine/Random.h"

namespace Game {

	Game::Game()
	{
		m_Player = new Player();
		InitPillars();
	}

	void Game::OnUpdate(float ts)
	{
		m_Player->OnUpdate(ts);

		for (size_t i = 0; i < MAX_AMOUNT_OF_PILLARS; i++)
		{
			m_Pillars[i].OnUpdate(ts);

			if (i % 2 == 0)
			{
				int startPlace = 1100.0f;

				if (m_Pillars[i].GetPosition().x + m_Pillars[i].GetWidth() < 0.0f)
				{
					SpawnPillars(m_Pillars[i], m_Pillars[i + 1], startPlace);
				}
			}
		}
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
		int tempRandX = Engine::Random::RangedRandom(1, 4);
		int tempRandY = Engine::Random::RangedRandom(0, 6);

		topPillar.SetPosition(sf::Vector2f(startPlace + DISTANCE_MULTIPLIER * tempRandX, MAX_POSITION_OF_PILLAR + (100.0f * tempRandY / 2)));

		tempRandY = Engine::Random::RangedRandom(tempRandY + 1, tempRandY + 3);

		bottomPillar.SetPosition(sf::Vector2f(startPlace + DISTANCE_MULTIPLIER * tempRandX, MIN_POSITION_OF_PILLAR + (100.0f * tempRandY / 2)));

		startPlace += DISTANCE_MULTIPLIER * tempRandX;
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