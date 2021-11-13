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

	private:

		sf::Texture m_Texture;
		sf::Sprite m_Sprite;

		const float DEFAULT_SPEED = 400.0f;

		float m_SpeedY = 400.0f;
	};

}