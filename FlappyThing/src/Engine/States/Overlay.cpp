#include "ftpch.h"
#include "Overlay.h"
#include "App.h"

namespace Engine {

	Overlay::Overlay()
	{
		m_ScreenWidth = Engine::Application::Get()->GetWindow()->GetWidth();
		m_ScreenHeight = Engine::Application::Get()->GetWindow()->GetHeight();

		SetInterface();
	}

	void Overlay::OnUpdate(float ts)
	{
		if (m_State == STATE::VISIBLE)
		{
			m_UI.OnUpdate(ts);
		}
	}

	void Overlay::OnEvent(sf::Event& e)
	{
		if (m_State == STATE::VISIBLE)
		{
			m_UI.OnEvent(e);
		}
	}

	void Overlay::OnRender(Engine::Graphics::Window* window)
	{
		if (m_State == STATE::VISIBLE)
		{
			window->Render(m_Layer);
			window->Render(m_Block);
			m_UI.OnRender(window);
		}
	}

	void Overlay::SwitchState()
	{
		if (m_State == STATE::VISIBLE)
		{
			m_State = STATE::HIDDEN;
		}
		else if (m_State == STATE::HIDDEN)
		{
			m_State = STATE::VISIBLE;
		}
	}

	void Overlay::SetInterface()
	{
		m_Layer.setFillColor(sf::Color(0, 0, 0, 200));
		m_Layer.setSize(sf::Vector2f(m_ScreenWidth, m_ScreenHeight));
		m_Texture.loadFromFile("res/sprites/button/block.png");
		m_Block.setTexture(m_Texture);
		m_Block.setOrigin(sf::Vector2f(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2));
		m_Block.setPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));


		m_UI.RegisterButton("RESUME", "res/sprites/button/button.png", false);
		m_UI.RegisterButton("EXIT TO MENU", "res/sprites/button/button.png", false);
		m_UI.RegisterButton("NEW GAME", "res/sprites/button/button.png", false);
		m_UI.GetButton("NEW GAME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));
		m_UI.GetButton("RESUME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 150.0f));
		m_UI.GetButton("EXIT TO MENU").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 150.0f));
	}

}