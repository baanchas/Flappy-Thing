#pragma once
#include "Engine/Graphics/Window.h"
#include "Button.h"

namespace Engine {

	class UIRegister
	{
	public:
		UIRegister();

		void OnRender(Graphics::Window* window);
		void OnEvent(sf::Event& e);
		void OnUpdate(float ts);

		void RegisterText(const std::string& string, int size = 24, bool outlineThickness = true);
		void RegisterButton(const std::string& text, const std::string& path, bool outlineThickness = true);

		sf::Text& GetText(const std::string& string) { auto element = m_TextRegister.find(string); return element->second; };
		UI::Button& GetButton(const std::string& string) { auto element = m_ButtonRegister.find(string); return element->second; };

	private:
		std::map<std::string, sf::Text> m_TextRegister;
		std::map<std::string, UI::Button> m_ButtonRegister;
		sf::Font m_DefaultFont;
	};

}