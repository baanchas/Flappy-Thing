#include "ftpch.h"
#include "Player.h"


#include "Engine/Random.h"
#include "App.h"


namespace Game {

	Player::Player()
	{
		m_Texture.loadFromFile("res/sprites/rocket/rocket.png");
		m_Texture.setSmooth(true);
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setScale(1.2f, 1.2f);
		m_Sprite.setOrigin((float)m_Texture.getSize().x / 2, (float)m_Texture.getSize().y / 2);
		m_Position = sf::Vector2f(Engine::Application::Get()->GetWindow()->GetWidth() / 2, 200.0f);
		m_Rotation = 90.0f;

		m_BoxCollider.setSize(COLLIDER_SIZE);
		m_BoxCollider.setOrigin(COLLIDER_SIZE.x / 2, COLLIDER_SIZE.y / 2);
		m_BoxCollider.setFillColor(sf::Color(1, 1, 1, 0));
		m_BoxCollider.setOutlineColor(sf::Color(255, 0, 0, 255));
		m_BoxCollider.setOutlineThickness(1);

		for (int i = 0; i < 8; i++)
		{
			m_Vertices.push_back(sf::Vector2f(0.0f, 0.0f));
		}
	}

	void Player::OnUpdate(float ts)
	{
		m_Sprite.setPosition(m_Position);
		m_Sprite.setRotation(m_Rotation);

		m_BoxCollider.setPosition(m_Position);
		m_BoxCollider.setRotation(m_Rotation);

		ComputeCoordinates();
		Move(sf::Vector2f(0.0f, m_SpeedY) * ts);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			AnimateFlying();
		}

		if (m_Rotation < 150)
		{
			m_Rotation += 3.0f;
		}

		if (m_SpeedY < MAX_SPEED)
		{
			m_SpeedY += 25.0f;
		}
	}

	void Player::OnEvent(sf::Event& e)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				m_SpeedY = -MAX_SPEED;
			}
		}

		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				m_SpeedY = -MAX_SPEED;
			}
		}

	}

	void Player::Render(Engine::Graphics::Window* window)
	{
		window->Render(m_Sprite);
		window->Render(m_BoxCollider);
	}

	void Player::AnimateFlying()
	{
		if (m_SpeedY < 0)
		{
			if (m_Rotation > 30)
			{
				if (m_Rotation > 90.0f)
				{
					m_Rotation = 90.0f;
				}

				m_Rotation -= 10.0f;
			}
		}
	}

	void Player::Reset()
	{
		m_Position = sf::Vector2f((float)Engine::Application::Get()->GetWindow()->GetWidth() / 2, (float)Engine::Application::Get()->GetWindow()->GetHeight() / 2);
		m_Rotation = 90.0f;
		m_SpeedY = MAX_SPEED;
		m_IsAlive = true;
	}

	void Player::ComputeCoordinates()
	{
		float tempx1 = -(m_BoxCollider.getSize().x / (float)2);
		float tempy1 = (m_BoxCollider.getSize().y / (float)2);

		float tempx2 = (m_BoxCollider.getSize().x / (float)2);
		float tempy2 = (m_BoxCollider.getSize().y / (float)2);

		float tempx3 = (m_BoxCollider.getSize().x / (float)2);
		float tempy3 = -(m_BoxCollider.getSize().y / (float)2);

		float tempx4 = -(m_BoxCollider.getSize().x / (float)2);
		float tempy4 = -(m_BoxCollider.getSize().y / (float)2);

		m_Vertices[0].x = tempx1 * cos(GetRotation()) - tempy1 * sin(GetRotation()) + GetPosition().x;
		m_Vertices[0].y = tempx1 * sin(GetRotation()) + tempy1 * cos(GetRotation()) + GetPosition().y;

		m_Vertices[1].x = tempx2 * cos(GetRotation()) - tempy2 * sin(GetRotation()) + GetPosition().x;
		m_Vertices[1].y = tempx2 * sin(GetRotation()) + tempy2 * cos(GetRotation()) + GetPosition().y;

		m_Vertices[2].x = tempx3 * cos(GetRotation()) - tempy3 * sin(GetRotation()) + GetPosition().x;
		m_Vertices[2].y = tempx3 * sin(GetRotation()) + tempy3 * cos(GetRotation()) + GetPosition().y;

		m_Vertices[3].x = tempx4 * cos(GetRotation()) - tempy4 * sin(GetRotation()) + GetPosition().x;
		m_Vertices[3].y = tempx4 * sin(GetRotation()) + tempy4 * cos(GetRotation()) + GetPosition().y;

		m_Vertices[4].x = (m_Vertices[0].x + m_Vertices[1].x) / 2;
		m_Vertices[4].y = (m_Vertices[0].y + m_Vertices[1].y) / 2;

		m_Vertices[5].x = (m_Vertices[1].x + m_Vertices[2].x) / 2;
		m_Vertices[5].y = (m_Vertices[1].y + m_Vertices[2].y) / 2;

		m_Vertices[6].x = (m_Vertices[2].x + m_Vertices[3].x) / 2;
		m_Vertices[6].y = (m_Vertices[2].y + m_Vertices[3].y) / 2;

		m_Vertices[7].x = (m_Vertices[3].x + m_Vertices[0].x) / 2;
		m_Vertices[7].y = (m_Vertices[3].y + m_Vertices[0].y) / 2;
	}

}