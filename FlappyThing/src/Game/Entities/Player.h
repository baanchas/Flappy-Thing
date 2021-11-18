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

		void Reset();

		void SetVitaliy(bool alive) { m_IsAlive = alive; };

		sf::Vector2u GetSize() { return m_Texture.getSize(); }
		std::vector<sf::Vector2f>& GetVerticesCoordinates() { return m_Vertices; };
		inline bool IsAlive() { return m_IsAlive; }

	private:
		void ComputeCoordinates();

	private:
		bool m_IsAlive = true;

		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
		
		sf::RectangleShape m_BoxCollider;
		std::vector<sf::Vector2f> m_Vertices;

		// constants

		const sf::Vector2f COLLIDER_SIZE = {26.0f, 50.0f};

		const float JUMP_SPEED = 500.0f;
		const float MAX_SPEED = 500.0f;

		float m_SpeedY = 400.0f;
	};

}