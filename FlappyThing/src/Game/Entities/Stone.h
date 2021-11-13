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

		inline sf::Vector2f& GetPosition() { return m_Position; };

		inline float GetWidth() { return WIDTH; }
		inline float GetHeight() { return HEIGHT; }

	private:
		sf::ConvexShape m_Triangle;

		const float DEFAULT_SPEED = 400.0f;
		const float WIDTH = 400.0f;
		const float HEIGHT = 600.0f;
		float m_SpeedX = 260.0f;
	};

}