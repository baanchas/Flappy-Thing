#include "ftpch.h"
#include "Stone.h"

namespace Game {

	Pillar::Pillar()
	{
		m_Triangle.setPointCount(3);

		m_Triangle.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		m_Triangle.setPoint(1, sf::Vector2f(WIDTH, 0.0f));
		m_Triangle.setPoint(2, sf::Vector2f(WIDTH / 2, HEIGHT));

		m_Triangle.setOrigin(WIDTH / 2, HEIGHT / 2);
	}

	void Pillar::OnUpdate(float ts)
	{
		Move(sf::Vector2f(m_SpeedX, 0.0f) * -ts);

		m_Triangle.setPosition(m_Position);
		m_Triangle.setRotation(m_Rotation);
	}

	void Pillar::OnEvent(sf::Event& e)
	{

	}

	void Pillar::Render(Engine::Graphics::Window* window)
	{
		window->Render(m_Triangle);
	}


}