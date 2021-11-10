#pragma once

#include "Graphics/Window.h"
#include "Engine/States/StateManager.h"
#include "Engine/States/Menu.h"

namespace Engine {

	class Application
	{
	public:
		~Application();

		void Run();

		void OnUpdate();
		void OnEvent();
		void OnRender();

		void Exit() { m_Running = false; };

		inline static Application& Get() { return *s_Instance; }

	private:
		Application();

	private:
		static Application* s_Instance;
		
		bool m_Running;

		Graphics::Window* m_Window;

		StateManager m_StateManager;

		Game::Menu* m_Menu;
	};

}