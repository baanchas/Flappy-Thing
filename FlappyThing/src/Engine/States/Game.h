#pragma once 

#include "State.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Stone.h"

namespace Game {

	class Game : public Engine::State
	{
	public:
		Game();
		~Game();

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;
		
		void InitPillars();
		void SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& startPlace);

		void Quit();
		void SetAvtive() override;
		inline bool Exit() override { return m_isQuit; }

		inline sf::View* GetCamera() { return m_Camera; };
		inline sf::Vector2f GetPlayerPosition() { return m_Player->GetPosition(); }
	private:

		sf::View* m_Camera;
		
		Player* m_Player;

		std::vector<Pillar> m_Pillars;

		sf::RectangleShape m_TopFloor;
		sf::RectangleShape m_BotFloor;

		int m_TempStartPlace = 0.0f;

		int m_Points = 0;
		
		bool m_AddPoints = false;

		sf::Text m_ScoreText;
		sf::Text m_PointsText;
		sf::Font m_DefaultFont;

		// constants

		const float SCALE = 30.0f;
		const float DEG = 57.0f;

		const int MAX_AMOUNT_OF_PILLARS = 8;
		const int MAX_POSITION_OF_PILLAR = -200;
		const int MIN_POSITION_OF_PILLAR = 500;
		const int START_X_COORD_OF_PILLARS = 1280;
		const int DISTANCE_MULTIPLIER = 100;
	};

}