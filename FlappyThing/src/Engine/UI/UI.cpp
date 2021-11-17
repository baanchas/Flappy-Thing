#include "ftpch.h"
#include "UI.h"
#include "App.h"

namespace Engine {

	UIRegister::UIRegister()
	{
		m_DefaultFont.loadFromFile("res/fonts/fasthand.ttf");
	}

	void UIRegister::OnUpdate(float ts)
	{
		std::map<std::string, UI::Button>::iterator itBtns;

		for (itBtns = m_ButtonRegister.begin(); itBtns != m_ButtonRegister.end(); itBtns++)
		{
			itBtns->second.OnUpdate(ts);

			GetText(itBtns->second.GetText()).setPosition(itBtns->second.GetPosition());
		}
	}

	void UIRegister::OnEvent(sf::Event& e)
	{
		std::map<std::string, UI::Button>::iterator itBtns;

		for (itBtns = m_ButtonRegister.begin(); itBtns != m_ButtonRegister.end(); itBtns++)
		{
			itBtns->second.OnEvent(e);
		}
	}

	void UIRegister::OnRender(Graphics::Window* window)
	{
		std::map<std::string, UI::Button>::iterator itBtns;

		for (itBtns = m_ButtonRegister.begin(); itBtns != m_ButtonRegister.end(); itBtns++)
		{
			itBtns->second.OnRender(window);
		}

		std::map<std::string, sf::Text>::iterator itTexts;

		for (itTexts = m_TextRegister.begin(); itTexts != m_TextRegister.end(); itTexts++)
		{
			window->Render(itTexts->second);
		}
	}
	
	void UIRegister::RegisterText(const std::string& string, int size, bool outlineThickness)
	{
		sf::Text text;
		text.setFont(m_DefaultFont);
		text.setString(string);
		text.setCharacterSize(size);
		text.setFillColor(sf::Color::Cyan);
		text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2));
		if (outlineThickness)
		{
			text.setOutlineColor(sf::Color::Red);
			text.setOutlineThickness(2);
		}

		m_TextRegister.emplace(string, text);
	}

	void UIRegister::RegisterButton(const std::string& name, const std::string& path, bool outlineThickness)
	{
		m_ButtonRegister.emplace(name, UI::Button(name, path));
		GetButton(name).SetTexture(path);
		GetButton(name).SetScale(0.5f);
		RegisterText(name, 30, outlineThickness);
	}

}