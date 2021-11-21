#pragma once

#include "Engine/Graphics/Window.h"
#include "Engine/States/StateManager.h"
#include "Engine/States/Menu.h"
#include "Engine/States/Game.h"

namespace Engine {

	class Application
	{
	// This class is Singleton
	public:
		~Application();

		// Runs the Main Loop
		void Run();

		// Main Loop functions

		void OnUpdate();
		void OnEvent();
		void OnRender();

		// ---------------------

		void PushState(State* state);
		void SetWindowCamera(sf::View* camera) { m_Window->SetCamera(camera); };

		void Exit() { m_Running = false; };

		// Gets the instance of this application
		inline static Application* Get() { return s_Instance; }

		// Getting the Window
		inline Graphics::Window* GetWindow() { return m_Window; }

		// Getting SFML window
		inline sf::RenderWindow* GetNativeWindow() { return m_Window->GetNativeWindow(); }

		inline Game::Menu* GetMenuState() { return m_Menu; };
		inline Game::Game* GetGameState() { return m_Game; };


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