#include "ftpch.h"
#include "Menu.h"
#include "App.h"

namespace Game {

	Menu::Menu()
	{
		
	}

	void Menu::OnUpdate(float ts)
	{
		std::cout << "Hi from menu!" << std::endl;
	}

	void Menu::OnEvent(sf::Event& e)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				std::cout << "pressed space";
				Engine::Application::Get()->PushState(Engine::Application::Get()->GetGameState());
			}
		}
		if (e.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "The right button was pressed" << std::endl;
			std::cout << "mouse x: " << e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << e.mouseButton.y << std::endl;
		}
	}

	void Menu::OnRender(Engine::Graphics::Window* window)
	{
	}

}