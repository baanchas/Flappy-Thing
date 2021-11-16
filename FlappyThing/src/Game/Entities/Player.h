#pragma once

#include "Engine/Entity/Entity.h"


namespace Game {

	class Player : public Engine::Entity
	{
	public:

		Player();
		~Player() {};

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void Render(Engine::Graphics::Window* window) override;

		void AnimateFlying();

		sf::Vector2u GetSize() { return m_Texture.getSize(); }
		sf::Vector2f* GetVerticesCoordinates() { return m_Vertices; };

	private:
		void ComputeCoordinates();

	private:

		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
		
		sf::RectangleShape m_BoxCollider;
		sf::Vector2f m_Vertices[4];

		const float JUMP_SPEED = 500.0f;
		const float MAX_SPEED = 500.0f;

		float m_SpeedY = 400.0f;
	};

}