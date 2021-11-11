#pragma once 

#include "State.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Stone.h"

namespace Game {

	class Game : public Engine::State
	{
	public:
		Game();

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;
		
		void InitPillars();
		void SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& startPlace);

		void Quit();
		void SetAvtive() override;

		inline bool Exit() override { return m_isQuit; }

	private:

		Player* m_Player;

		std::vector<Pillar> m_Pillars;
		//sf::RectangleShape rect;

		const int MAX_AMOUNT_OF_PILLARS = 6;
		const int MAX_POSITION_OF_PILLAR = -200;
		const int MIN_POSITION_OF_PILLAR = 500;
		const int DISTANCE_MULTIPLIER = 300;
		const int START_X_COORD_OF_PILLARS = 1280;
	};

}