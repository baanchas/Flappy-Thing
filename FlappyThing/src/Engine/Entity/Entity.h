#pragma once

namespace Engine {

	class Entity
	{
	public:

		virtual void OnUpdate(float ts) = 0;
		virtual void OnEvent(sf::Event& e) = 0;
		virtual void Render(Graphics::Window* window) = 0;

		virtual void Move(const sf::Vector2f& vector);

		virtual void SetPosition(const sf::Vector2f& vector);
		virtual void SetRotation(const float& rotation);

		virtual inline sf::Vector2f& GetPosition() { return m_Position; };
		virtual inline float& GetRotation() { return m_Rotation; };


	protected:

		sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
		float m_Rotation = 0;
	};

}