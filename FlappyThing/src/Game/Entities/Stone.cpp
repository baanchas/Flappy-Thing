#include "ftpch.h"
#include "Stone.h"

namespace Game {

	Pillar::Pillar()
	{
		m_Vertex_1 = sf::Vector2f(0.0f, 0.0f);
		m_Vertex_2 = sf::Vector2f(WIDTH, 0.0f);
		m_Vertex_3 = sf::Vector2f(WIDTH / 2, HEIGHT);

		m_Rect.setOrigin(WIDTH / 2, HEIGHT / 2);
		m_Rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
		
		m_Vertices.push_back(new sf::Vector2f());
		m_Vertices.push_back(new sf::Vector2f());
		m_Vertices.push_back(new sf::Vector2f());
	}

	void Pillar::OnUpdate(float ts)
	{
		Move(sf::Vector2f(m_SpeedX, 0.0f) * -ts);

		*m_Vertices[0] = sf::Vector2f(GetPosition().x - WIDTH / 2, GetPosition().y - HEIGHT / 2);
		*m_Vertices[1] = sf::Vector2f(GetPosition().x - WIDTH / 2, GetPosition().y + HEIGHT / 2);
		*m_Vertices[2] = sf::Vector2f(GetPosition().x + WIDTH / 2, GetPosition().y - HEIGHT / 2);

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

	std::vector<sf::Vector2f*>& Pillar::GetVertices()
	{
		return m_Vertices;
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