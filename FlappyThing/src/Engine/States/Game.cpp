#include "ftpch.h"
#include "Engine/States/Game.h"

namespace Game {

	Game::Game()
	{
		rect.setSize(sf::Vector2f(200.0f, 200.0f));
	}

	void Game::OnUpdate(float ts)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			rect.setPosition(rect.getPosition() + sf::Vector2f(10.0f, 0.0f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			rect.setPosition(rect.getPosition() + sf::Vector2f(-10.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rect.setPosition(rect.getPosition() + sf::Vector2f(0.0f, -10.0f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			rect.setPosition(rect.getPosition() + sf::Vector2f(0.0f, 10.0f));
		}
	}

	void Game::OnEvent(sf::Event& e)
	{
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
		window->Render(rect);
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