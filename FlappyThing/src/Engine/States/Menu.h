#pragma once

#include "State.h"

namespace Game {

	class Menu : public Engine::State
	{
	public:

		Menu();
		~Menu();

		void OnUpdate() override;
		void OnEvent(sf::Event& e) override;
		void OnRender() override;

	private:

	};

}