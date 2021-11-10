#pragma once 

#include "State.h"

namespace Game {

	class Game : public Engine::State
	{
	public:
		Game();

		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void OnRender(Engine::Graphics::Window* window) override;
		

		void Quit();
		void SetAvtive() override;

		inline bool Exit() override { return m_isQuit; }

	private:

		sf::RectangleShape rect;

	};

}