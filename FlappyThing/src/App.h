#pragma once

#include "Graphics/Window.h"
#include "Engine/States/StateManager.h"
#include "Engine/States/Menu.h"
#include "Engine/States/Game.h"

namespace Engine {

	class Application
	{
	public:
		~Application();

		void Run();

		void OnUpdate();
		void OnEvent();
		void OnRender();

		void PushState(State* state);

		void Exit() { m_Running = false; };

		inline static Application& Get() { return *s_Instance; }

		Game::Menu* GetMenuState() { return m_Menu; };
		Game::Game* GetGameState() { return m_Game; };

	private:
		Application();

	private:
		static Application* s_Instance;
		
		bool m_Running;

		Graphics::Window* m_Window;

		StateManager m_StateManager;

		Game::Menu* m_Menu;
		Game::Game* m_Game;

		sf::Clock m_Clock;
		float m_TimeStep;
		float m_LastFrameTime;
	};

}