#include "ftpch.h"
#include "App.h"

namespace Engine {
	//setVerticalSyncEnabled
	Application* Application::s_Instance = new Application();

	Application::Application()
	{
		m_Window = new Graphics::Window();
		m_Running = true;

		m_Menu = new Game::Menu();
		m_StateManager.PushState(m_Menu);
	}

	Application::~Application()
	{
		delete s_Instance;
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear();
			
			OnEvent();
			OnUpdate();
			OnRender();

			m_Window->Display();
		}
	}

	void Application::OnUpdate()
	{
		m_StateManager.GetTop()->OnUpdate();
	}

	void Application::OnRender()
	{
		m_StateManager.GetTop()->OnRender();
	}

	void Application::OnEvent()
	{
		sf::Event e;

		while (m_Window->GetNativeWindow()->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_Window->GetNativeWindow()->close();
				m_Running = false;
			}
			
			m_StateManager.GetTop()->OnEvent(e);
		}

	}

}