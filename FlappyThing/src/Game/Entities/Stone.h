#pragma once

#include "Engine/Entity/Entity.h"


namespace Game {

	class Pillar : public Engine::Entity
	{
	public:

		Pillar();
		~Pillar() {};

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void Render(Engine::Graphics::Window* window) override;

		void SetAsAddable(bool condition) { m_isAddedToPoints = condition; }
		void SetColor(sf::Color color) { m_Rect.setFillColor(color); }
		inline sf::Vector2f& GetPosition() { return m_Position; };

		inline float GetWidth() { return WIDTH; }
		inline float GetHeight() { return HEIGHT; }
		inline bool& CanAddToPoints() { return m_isAddedToPoints; }

		std::vector<sf::Vector2f*>& GetVertices();

		bool Contains(const sf::Vector2f& rect);


	private:

		bool m_isAddedToPoints = false;
		//sf::ConvexShape m_Triangle;
		sf::RectangleShape m_Rect;
		std::vector<sf::Vector2f*> m_Vertices;

		sf::Vector2f m_Vertex_1;
		sf::Vector2f m_Vertex_2;
		sf::Vector2f m_Vertex_3;

		const float DEFAULT_SPEED = 400.0f;
		const float WIDTH = 100.0f;
		const float HEIGHT = 600.0f;
		float m_SpeedX = 260.0f;
	};

}