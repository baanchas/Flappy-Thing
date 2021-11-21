#include "ftpch.h"
#include "Button.h"
#include "App.h"

namespace Engine {	namespace UI {

	Button::Button(const std::string& text, const std::string& path)
	{
		m_Texture.loadFromFile(path);
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setOrigin(sf::Vector2f(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2));
		m_Sprite.setColor(m_DefaultColor);
		m_Text = text;
	}

	void Button::OnUpdate(float ts)
	{
		// set color hovered, clicked or pressed colors

		switch (STATE)
		{
		case ButtonState::NONE:
			m_Sprite.setColor(m_DefaultColor);
			break;
		case ButtonState::HOVER:
			m_Sprite.setColor(m_HoveredColor);
			break;
		case ButtonState::CLICK:
			m_Sprite.setColor(m_ClickedColor);
			break;
		case ButtonState::PRESS:
			m_Sprite.setColor(m_ClickedColor);
			break;
		case ButtonState::UNACTIVE:
			m_Sprite.setColor(m_UnActiveColor);
			break;
		}

		// change condition to PRESS if button is pressed

		if (STATE != ButtonState::UNACTIVE)
		{
			STATE = ButtonState::NONE;

			m_Size = sf::Vector2f(m_Texture.getSize().x, m_Texture.getSize().y);
			m_Sprite.setPosition(m_Position);

			// check if button sprite contains cursor
			if (m_Sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*Engine::Application::Get()->GetNativeWindow()).x, sf::Mouse::getPosition(*Engine::Application::Get()->GetNativeWindow()).y)))
			{
				STATE = ButtonState::HOVER;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					STATE = ButtonState::PRESS;
				}
			}
		}
	}

	void Button::OnEvent(sf::Event& e)
	{
		// change condition to CLICK if button is clicked

		if (STATE != ButtonState::UNACTIVE)
		{
			if (m_Sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*Engine::Application::Get()->GetNativeWindow()).x, sf::Mouse::getPosition(*Engine::Application::Get()->GetNativeWindow()).y)))
			{
				STATE = ButtonState::HOVER;

				if (e.type == sf::Event::MouseButtonPressed)
				{
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						STATE = ButtonState::CLICK;
					}
				}
			}
		}
	}

	void Button::OnRender(Engine::Graphics::Window* window)
	{
		window->Render(m_Sprite);
	}

	void Button::SetPosition(const sf::Vector2f& vector)
	{
		m_Position = vector;
	}

	void Button::SetTexture(const std::string& path)
	{
		m_Texture.loadFromFile(path);
		m_Sprite.setTexture(m_Texture);
	}

	// change condition to HOVER if button is hovered

	bool Button::IsHovered()
	{
		if (STATE == ButtonState::HOVER)
		{
			return true;
		}
		return false;
	}

	// check if the button CLICKED

	bool Button::IsClicked()
	{
		if (STATE == ButtonState::CLICK)
		{
			return true;
		}
		return false;
	}

	// check if the button PRESSED

	bool Button::IsPressed()
	{
		if (STATE == ButtonState::PRESS)
		{
			return true;
		}
		return false;
	}

}}