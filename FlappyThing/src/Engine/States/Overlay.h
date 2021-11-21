#pragma once

#include "Engine/UI/UI.h"

namespace Engine {

	enum class STATE
	{
		HIDDEN = 0,
		VISIBLE
	};

	class Overlay
	{
	public:

		Overlay();
		~Overlay() {};

		void OnUpdate(float ts);
		void OnEvent(sf::Event& e);
		void OnRender(Engine::Graphics::Window* window);

		void SetInterface();

		Engine::UIRegister& GetUI() { return m_UI; };
	private:

		float m_ScreenWidth;
		float m_ScreenHeight;

		sf::RectangleShape m_Layer;

		sf::Texture m_Texture;
		sf::Sprite m_Block;

		Engine::UIRegister m_UI;
	};

}