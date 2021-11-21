#pragma once 

#include "State.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Pillar.h"
#include "Engine/UI/UI.h"
#include "Engine/States/Overlay.h"
#include "Engine/ParticleSystem/ObjectGenerator.h"

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
		
		void OnUpdatePLAY(float ts);

		void InitMap();
		void InitPillars();
		void CollisionTest(sf::Vector2f vector);
		void SpawnPillars(Pillar& topPillar, Pillar& bottomPillar, int& startPlace);

		void SetColors();
		void CountPoints(int i);
		void Reset();
		void SwitchState();

		void SetAndSavePoints(int points);

		void Quit();
		void SetActive() override;
		inline bool Exit() override { return m_isQuit; }

		bool GetPLayerVitalityState() { return m_Player->IsAlive(); }

		inline sf::Vector2f GetPlayerPosition() { return m_Player->GetPosition(); }

		inline int GetHighPoints() { return m_HighPoints; }

	public:
		GAMESTATE m_State = GAMESTATE::PLAY;
		Engine::Overlay m_PauseOverlay;

	private:
		
		Player* m_Player;

		Engine::CircleProps m_StarProps;
		Engine::ObjectGenerator m_StarGenerator = Engine::ObjectGenerator(20);

		Engine::UIRegister m_UI;
		
		std::vector<Pillar> m_PillarsPool;
		std::ifstream m_ToRead;
		std::ofstream m_ToWrite;
		
		sf::RectangleShape m_TopFloor;
		sf::RectangleShape m_BotFloor;

		sf::Texture m_WallpaperTexture;
		sf::Sprite m_WallpaperSprite;

		Color m_Color;

		uint32_t m_ScreenWidth;
		uint32_t m_ScreenHeight;

		int m_Points = 0;
		int m_HighPoints = 0;
		int m_TempStartPlace = 0;

		// constants

		const int MAX_AMOUNT_OF_PILLARS = 8;
		const float MAX_POSITION_OF_PILLAR = -200;
		const float MIN_POSITION_OF_PILLAR = 500;
		const float START_X_COORD_OF_PILLARS = 1280;
		const float DISTANCE_MULTIPLIER = 100;
	};

}