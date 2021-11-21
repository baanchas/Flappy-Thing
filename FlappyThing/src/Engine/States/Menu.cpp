#include "ftpch.h"

#include "Menu.h"
#include "App.h"

namespace Game {

	Menu::Menu()
	{
		m_ScreenWidth = Engine::Application::Get()->GetWindow()->GetWidth();
		m_ScreenHeight = Engine::Application::Get()->GetWindow()->GetHeight();

		m_Player.SetPosition(sf::Vector2f(100.0f, 100.0f));

		m_Player.m_SmokeProps.SpeedRandomRangeX = sf::Vector2i(-3, 3);
		m_Player.m_SmokeProps.SpeedRandomRangeY = sf::Vector2i(-3, 3);
		m_Player.m_SmokeProps.LifeTime = 10.0f;

		InitUI();

		m_StarProps.Radius = sf::Vector2i(1, 4);
		m_StarProps.PositionX = sf::Vector2f(1300, 1700);
		m_StarProps.PositionY = sf::Vector2f(-200, 300);
		m_StarProps.SpeedRandomRangeX = sf::Vector2i(-250, -100);
		m_StarProps.SpeedRandomRangeY = sf::Vector2i(0, 100);
		m_StarProps.Time = sf::Vector2i(1, 10);
	}

	void Menu::OnUpdate(float ts)
	{
		// Handle button events

		if (m_UI.GetButton("RESUME").IsClicked())
		{
			Engine::Application::Get()->PushState(Engine::Application::Get()->GetGameState());
		}

		if (m_UI.GetButton("NEW GAME").IsClicked())
		{
			Engine::Application::Get()->GetGameState()->m_State = GAMESTATE::PLAY;
			Engine::Application::Get()->GetGameState()->Reset();
			Engine::Application::Get()->PushState(Engine::Application::Get()->GetGameState());
		}

		if (m_UI.GetButton("EXIT").IsClicked())
		{
			Engine::Application::Get()->Exit();
		}

		m_UI.OnUpdate(ts);

		if (Engine::Application::Get()->GetGameState()->GetPLayerVitalityState())
		{
			m_UI.GetButton("RESUME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 150.0f));
			m_UI.GetButton("NEW GAME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));
			m_UI.GetButton("EXIT").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 150.0f));
		}
		else
		{
			m_UI.GetButton("RESUME").SetPosition(sf::Vector2f(-1000.0f, -1000.0f));
			m_UI.GetButton("NEW GAME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 100.0f));
			m_UI.GetButton("EXIT").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 100.0f));
		}

		// Making the Rocket follow the Cursor

		sf::Vector2i mousePos = sf::Mouse::getPosition(*Engine::Application::Get()->GetNativeWindow());

		sf::Vector2f playerPos;

		float distX = mousePos.x - m_Player.GetPosition().x;
		float distY = mousePos.y - m_Player.GetPosition().y;

		playerPos.x = distX / 5 * PLAYER_SPEED * ts;
		playerPos.y = distY / 5 * PLAYER_SPEED * ts;

		float PI = 3.14159265;

		float rotation = (atan2(distY, distX)) * 180 / PI;

		m_Player.SetPosition(playerPos + m_Player.GetPosition());
		m_Player.SetRotation(rotation + 90.0f);

		m_Player.SetTransformation();
		m_Player.ComputeCoordinates();
		m_Player.UpdateSmoke(ts, sf::Vector2f(0.0f, 0.0f));

		// Setting High Points text

		std::string points = std::to_string(Engine::Application::Get()->GetGameState()->GetHighPoints());
		m_UI.GetText("HIGH_SCORE").setString(points);

		// Making stars fall

		m_StarGenerator.OnUpdate(ts, m_StarProps);
	}

	void Menu::OnEvent(sf::Event& e)
	{
		m_UI.OnEvent(e);
	}

	void Menu::OnRender(Engine::Graphics::Window* window)
	{
		window->Render(m_Block);
		m_StarGenerator.OnRender(window);
		m_UI.OnRender(window);
		m_Player.Render(window);
	}

	void Menu::InitUI()
	{
		m_BlockTexture.loadFromFile("res/sprites/button/block.png");
		m_BlockTexture.setSmooth(true);
		m_Block.setTexture(m_BlockTexture);
		m_Block.setOrigin(m_BlockTexture.getSize().x / 2, m_BlockTexture.getSize().y / 2);
		m_Block.setPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2));
		m_Block.setScale(0.7f, 1.0f);

		m_UI.RegisterText("FLAPPY ROCKET");
		m_UI.GetText("FLAPPY ROCKET").setCharacterSize(40);
		sf::Vector2f size = sf::Vector2f(m_UI.GetText("FLAPPY ROCKET").getLocalBounds().width / 2, m_UI.GetText("FLAPPY ROCKET").getLocalBounds().height / 2);
		m_UI.GetText("FLAPPY ROCKET").setOrigin(size);
		m_UI.GetText("FLAPPY ROCKET").setPosition(Engine::Application::Get()->GetWindow()->GetWidth() / 2, 50.0f);

		m_UI.RegisterText("HIGH SCORE: ");
		m_UI.RegisterText("HIGH_SCORE");
		m_UI.GetText("HIGH SCORE: ").setCharacterSize(40);
		m_UI.GetText("HIGH_SCORE").setCharacterSize(40);
		m_UI.GetText("HIGH SCORE: ").setOrigin(m_UI.GetText("HIGH SCORE: ").getLocalBounds().width / 2, m_UI.GetText("HIGH SCORE: ").getLocalBounds().height / 2);
		m_UI.GetText("HIGH_SCORE").setOrigin(m_UI.GetText("HIGH_SCORE").getLocalBounds().width / 2, m_UI.GetText("HIGH_SCORE").getLocalBounds().height / 2);
		m_UI.GetText("HIGH SCORE: ").setPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 300.0f));
		m_UI.GetText("HIGH_SCORE").setPosition(sf::Vector2f(m_ScreenWidth / 2 + m_UI.GetText("HIGH SCORE: ").getLocalBounds().width + 20.0f, m_ScreenHeight / 2 + 300.0f));

		m_UI.RegisterButton("RESUME", "res/sprites/button/button.png");
		m_UI.RegisterButton("NEW GAME", "res/sprites/button/button.png");
		m_UI.RegisterButton("EXIT", "res/sprites/button/button.png");

		m_UI.GetButton("RESUME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 100.0f));
		m_UI.GetButton("NEW GAME").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 - 100.0f));
		m_UI.GetButton("EXIT").SetPosition(sf::Vector2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 100.0f));
	}

}