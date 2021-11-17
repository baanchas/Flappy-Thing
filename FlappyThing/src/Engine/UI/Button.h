#pragma once

namespace Engine {	namespace UI {
	
	enum class ButtonState
	{
		NONE = 0,
		CLICK,
		PRESS,
		HOVER,
		UNACTIVE
	};

	class Button
	{
	public:

		Button(const std::string& text, const std::string& path);
		~Button() {};

		void OnUpdate(float ts);
		void OnEvent(sf::Event& e);
		void OnRender(Engine::Graphics::Window* window);

		void SetPosition(const sf::Vector2f& vector);
		void SetTexture(const std::string& path);
		void SetScale(float scale) { m_Sprite.setScale(scale, scale); }

		void SetActive() { STATE = ButtonState::NONE; };
		void SetUnActive() { STATE = ButtonState::UNACTIVE; };

		bool IsHovered();
		bool IsClicked();
		bool IsPressed();


		Button(const Button&) = default;

		inline sf::Vector2f GetPosition() { return m_Position; }
		inline std::string GetText() { return m_Text; }
		inline sf::Vector2f GetSize() {	return m_Size; }

	private:
		ButtonState STATE = ButtonState::NONE;
		std::string m_Text;

		sf::Texture m_Texture;
		sf::Sprite m_Sprite;

		sf::Vector2f m_Size;
		sf::Vector2f m_Position;

		sf::Color m_DefaultColor = sf::Color(255, 255, 255, 255);
		sf::Color m_HoveredColor = sf::Color(155, 155, 155, 255);
		sf::Color m_ClickedColor = sf::Color(255, 255, 155, 155);
		sf::Color m_UnActiveColor = sf::Color(55, 55, 55, 255);
	};

}}