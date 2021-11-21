#pragma once

#include "State.h"
#include "Engine/UI/UI.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include "Game/Entities/Player.h"
#include "Engine/ParticleSystem/ObjectGenerator.h"

namespace Game {

	//class Application;
	struct ParticleProps;
	struct Particle;
	class ParticleSystem;

	class Menu : public Engine::State
	{
	public:

		Menu();
		~Menu() {};

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;

		void InitUI();

	private:
		Player m_Player;

		Engine::UIRegister m_UI;

		sf::Texture m_BlockTexture;
		sf::Sprite m_Block;

		uint32_t m_ScreenWidth;
		uint32_t m_ScreenHeight;
		
		Engine::CircleProps m_StarProps;
		Engine::ObjectGenerator m_StarGenerator = Engine::ObjectGenerator(10);

		// constants

		const float PLAYER_SPEED = 5.0f;
	};

}