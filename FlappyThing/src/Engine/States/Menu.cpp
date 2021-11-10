#include "ftpch.h"
#include "Menu.h"

namespace Game {

	Menu::Menu()
	{
		std::cout << "Menu is Pushed!";
	}

	void Menu::OnUpdate()
	{
		//std::cout << "Hi from menu!" << std::endl;
	}

	void Menu::OnEvent(sf::Event& e)
	{
		if (e.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "The right button was pressed" << std::endl;
			std::cout << "mouse x: " << e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << e.mouseButton.y << std::endl;
		}
	}

	void Menu::OnRender()
	{
	}

}