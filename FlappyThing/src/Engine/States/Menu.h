#pragma once


#include "State.h"

namespace Game {

	class Application;

	class Menu : public Engine::State
	{
	public:

		Menu();
		~Menu() {};

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;

	private:
	};

}