#include "ftpch.h"
#include "Overlay.h"
#include "App.h"

namespace Engine {

	// PAUSE overlay

	Overlay::Overlay()
	{
		m_ScreenWidth = Engine::Application::Get()->GetWindow()->GetWidth();
		m_ScreenHeight = Engine::Application::Get()->GetWindow()->GetHeight();

		SetInterface();
	}

	void Overlay::OnUpdate(float ts)
	{
		auto Game = Engine::Application::Get()->GetGameState();

		if (Game->m_State == Game::GAMESTATE::PAUSE)
		{
			if (m_UI.GetButton("START AGAIN").IsClicked())
			{
				Game->Reset();
				Game->SwitchState();
			}

			if (m_UI.GetButton("EXIT TO MENU").IsClicked())
			{
				Game->Quit();
			}
		}
		m_UI.OnUpdate(ts);
	}

	void Overlay::OnEvent(sf::Event& e)
	{
		m_UI.OnEvent(e);
	}

	void Overlay::OnRender(Engine::Graphics::Window* window)
	{
		window->Render(m_Layer);
		window->Render(m_Block);
		m_UI.OnRender(window);
	}

	void Overlay::SetInterface()
	{
		m_Layer.setFillColor(sf::Color(0, 0, 0, 200));
		m_Layer.setSize(sf::Vector2f(m_ScreenWidth, m_ScreenHeight));

		m_Texture.loadFromFile("res/sprites/button/block.png");
		m_Block.setTexture(m_Texture);
		m_Block.setScale(0.7f, 1.0f);
		m_Block.setOrigin(sf::Vector2f(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2));
		m_Block.setPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));

		m_UI.RegisterText("HIGH SCORE: ");
		m_UI.RegisterText("HIGH_SCORE");
		m_UI.GetText("HIGH SCORE: ").setCharacterSize(40);
		m_UI.GetText("HIGH_SCORE").setCharacterSize(40);
		m_UI.GetText("HIGH SCORE: ").setOrigin(m_UI.GetText("HIGH SCORE: ").getLocalBounds().width / 2, m_UI.GetText("HIGH SCORE: ").getLocalBounds().height / 2);
		m_UI.GetText("HIGH_SCORE").setOrigin(m_UI.GetText("HIGH_SCORE").getLocalBounds().width / 2, m_UI.GetText("HIGH_SCORE").getLocalBounds().height / 2);
		m_UI.GetText("HIGH SCORE: ").setPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 300.0f));
		m_UI.GetText("HIGH_SCORE").setPosition(sf::Vector2f(m_ScreenWidth / 2 + m_UI.GetText("HIGH SCORE: ").getLocalBounds().width + 20.0f, m_ScreenHeight / 2 + 300.0f));

		m_UI.RegisterButton("EXIT TO MENU", "res/sprites/button/button.png", false);
		m_UI.RegisterButton("START AGAIN", "res/sprites/button/button.png", false);
		m_UI.GetButton("START AGAIN").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 100.0f));
		m_UI.GetButton("EXIT TO MENU").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 100.0f));
	}

}