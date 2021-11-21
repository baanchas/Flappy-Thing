#include "ftpch.h"
#include "Pillar.h"

namespace Game {

	Pillar::Pillar()
	{
		// init sprite
		m_Rect.setPosition(sf::Vector2f(-500.f, -500.0f));
		m_Rect.setOrigin(WIDTH / 2, HEIGHT / 2);
		m_Rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
	}

	void Pillar::OnUpdate(float ts)
	{
		Move(sf::Vector2f(m_SpeedX, 0.0f) * -ts);

		m_Rect.setPosition(m_Position);
		m_Rect.setRotation(m_Rotation);
	}

	void Pillar::OnEvent(sf::Event& e)
	{

	}

	void Pillar::Render(Engine::Graphics::Window* window)
	{
		window->Render(m_Rect);
	}

	bool Pillar::Contains(const sf::Vector2f& vector)
	{
		if (m_Rect.getGlobalBounds().contains(vector))
		{
			return true;
		}
		return false;
	}


}