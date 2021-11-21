#include "ftpch.h"
#include "App.h"
#include "Engine/Random.h"

namespace Engine {
	
	Application* Application::s_Instance = new Application();

	Application::Application()
	{
		s_Instance = this;

		m_Window = new Graphics::Window();
		m_Running = true;

		m_Menu = new Game::Menu();
		m_StateManager.PushState(m_Menu);

		m_Game = new Game::Game();

		Random::Init();
		//m_StateManager.PushState(m_Game);
	}

	Application::~Application()
	{
		delete s_Instance;
		delete m_Window;
		delete m_Game;
		delete m_Menu;
	}

	// MAIN LOOP

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear(sf::Color(40, 40, 40, 255));
			
			OnEvent();
			OnUpdate();
			OnRender();

			m_Window->Display();

			if (m_StateManager.GetTop()->Exit())
			{
				m_StateManager.Pop();
			}
		}
	}

	// Main on update fucntion of the Engine that iterates every frame

	void Application::OnUpdate()
	{
		// getting Time Step (delta time) of the frame
		float time = (float)m_Clock.getElapsedTime().asSeconds();
		m_TimeStep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		m_Window->OnUpdate(m_TimeStep);

		// calling update of top state in state manager stack
		m_StateManager.GetTop()->OnUpdate(m_TimeStep);
	}

	// Main on render fucntion of the Engine that iterates every frame

	void Application::OnRender()
	{
		// calling update of top state in state manager stack
		m_StateManager.GetTop()->OnRender(m_Window);
	}

	// Main on event function that handles events of the Window

	void Application::OnEvent()
	{
		sf::Event e;

		// waiting for event and sending it through engine
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

	void Application::PushState(State* state)
	{
		state->SetActive();

		m_StateManager.PushState(state);
	}

}