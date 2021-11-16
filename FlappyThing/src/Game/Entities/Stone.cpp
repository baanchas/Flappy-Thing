#include "ftpch.h"
#include "Stone.h"

namespace Game {

	Pillar::Pillar()
	{
		//m_Triangle.setPointCount(3);

		m_Vertex_1 = sf::Vector2f(0.0f, 0.0f);
		m_Vertex_2 = sf::Vector2f(WIDTH, 0.0f);
		m_Vertex_3 = sf::Vector2f(WIDTH / 2, HEIGHT);

		/*m_Triangle.setPoint(0, m_Vertex_1);
		m_Triangle.setPoint(1, m_Vertex_2);
		m_Triangle.setPoint(2, m_Vertex_3);*/

		m_Rect.setOrigin(WIDTH / 2, HEIGHT / 2);
		m_Rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
		//m_Triangle.setOrigin(WIDTH / 2, HEIGHT / 2);
		
		m_Vertices.push_back(new sf::Vector2f());
		m_Vertices.push_back(new sf::Vector2f());
		m_Vertices.push_back(new sf::Vector2f());

		//std::cout << m_Vertices[0].x <<  " " << m_Vertices[0].y << std::endl;
		//std::cout << m_Vertices[1].x <<  " " << m_Vertices[1].y << std::endl;
	
	}

	void Pillar::OnUpdate(float ts)
	{
		Move(sf::Vector2f(m_SpeedX, 0.0f) * -ts);

		//std::cout << GetPosition().x << std::endl;

		*m_Vertices[0] = sf::Vector2f(GetPosition().x - WIDTH / 2, GetPosition().y - HEIGHT / 2);
		//std::cout << m_Vertex_1.x << " " << m_Vertex_1.y << std::endl;
		*m_Vertices[1] = sf::Vector2f(GetPosition().x - WIDTH / 2, GetPosition().y + HEIGHT / 2);
		//std::cout << m_Vertex_2.x << " " << m_Vertex_3.y << std::endl;
		*m_Vertices[2] = sf::Vector2f(GetPosition().x + WIDTH / 2, GetPosition().y - HEIGHT / 2);
		//std::cout << m_Vertex_3.x << " " << m_Vertex_3.y << std::endl;

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
		if (GetPosition().x - WIDTH / 2 < vector.x 
			&& GetPosition().x + WIDTH / 2 > vector.x
			&& GetPosition().y + HEIGHT/ 2 > vector.y
			&& GetPosition().y - HEIGHT / 2 < vector.y)
		{
			return true;
		}
		return false;
	}


}