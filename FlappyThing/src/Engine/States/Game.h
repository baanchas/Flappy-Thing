#pragma once 

#include "State.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Stone.h"
#include "Engine/UI/UI.h"
#include "Engine/States/Overlay.h"


namespace Game {

	struct Color
	{
		int R = 0, G = 255, B = 120, incrementR = 1, incrementB = 1, incrementG = 1;
	};

	enum class GAMESTATE
	{
		PAUSE = 0,
		PLAY
	};

	class Game : public Engine::State
	{
	public:
		Game();
		~Game();

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;
		
		void InitMap();
		void InitPillars();
		void SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& startPlace);
		void CollisionTest();
		void CountPoints(int i);
		void SetColors();

		void Reset();
		void SwitchState();

		void Quit();
		void SetAvtive() override;
		inline bool Exit() override { return m_isQuit; }

		inline sf::View* GetCamera() { return m_Camera; };
		inline sf::Vector2f GetPlayerPosition() { return m_Player->GetPosition(); }
	private:
		GAMESTATE m_State = GAMESTATE::PLAY;

		Engine::Overlay m_PauseOverlay;

		Player* m_Player;

		sf::View* m_Camera;
		
		Engine::UIRegister m_UI;

		std::vector<Pillar> m_Pillars;

		sf::RectangleShape m_TopFloor;
		sf::RectangleShape m_BotFloor;

		int m_TempStartPlace = 0;

		int m_Points = 0;

		uint32_t m_ScreenWidth;
		uint32_t m_ScreenHeight;

		Color m_Color;

		// constants

		const float SCALE = 30.0f;
		const float DEG = 57.0f;

		const int MAX_AMOUNT_OF_PILLARS = 8;
		const float MAX_POSITION_OF_PILLAR = -200;
		const float MIN_POSITION_OF_PILLAR = 500;
		const float START_X_COORD_OF_PILLARS = 1280;
		const float DISTANCE_MULTIPLIER = 100;
	};

}