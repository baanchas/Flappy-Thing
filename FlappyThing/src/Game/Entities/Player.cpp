#include "ftpch.h"
#include "Player.h"
#include "App.h"

#include "Engine/Random.h"

namespace Game {

	Player::Player()
	{
		m_Texture.loadFromFile("res/sprites/rocket/rocket.png");
		m_Texture.setSmooth(true);
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setScale(1.2f, 1.2f);
		m_Sprite.setOrigin(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2);
		m_Position = sf::Vector2f(640.0f, 0.0f);
		m_Rotation = 90.0f;
	}

	void Player::OnUpdate(float ts)
	{
		Move(sf::Vector2f(0.0f, m_SpeedY) * ts);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			AnimateFlying();
		}

		if (m_Rotation < 180)
		{
			m_Rotation += 3.0f;
		}

		if (m_SpeedY < DEFAULT_SPEED)
		{
			m_SpeedY += 25.0f;
		}

		m_Sprite.setPosition(m_Position);
		m_Sprite.setRotation(m_Rotation);
	}

	void Player::OnEvent(sf::Event& e)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				m_SpeedY = -500.0f;
			}
		}

	}

	void Player::Render(Engine::Graphics::Window* window)
	{
		window->Render(m_Sprite);
	}

	void Player::AnimateFlying()
	{
		if (m_SpeedY < 0)
		{
			if (m_Rotation > 0)
			{
				if (m_Rotation > 90.0f)
				{
					m_Rotation = 90.0f;
				}

				m_Rotation -= 10.0f;
			}
		}
		//m_Sprite.setRotation((m_SpeedY / (DEFAULT_SPEED / 90.0f) + 90.0f));
	}


}