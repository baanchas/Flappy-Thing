#pragma once 

namespace Engine {

	struct CircleProps
	{
		sf::Vector2f PositionX, PositionY;
		sf::Vector2i SpeedRandomRangeX{ -5, 5 }, SpeedRandomRangeY{ -5, 5 };
		sf::Color Color;
		int Speed;
		sf::Vector2i Time;
		sf::Vector2i Radius;
	};

	struct Circle
	{
		sf::Vector2f Position;
		sf::Vector2f Speed;
		sf::Vector2f Size;
		sf::Color Color;

		float Time = -1.0f;
		float Radius = 0.0f;

		sf::CircleShape ShapeCircle;
	};

	class ObjectGenerator
	{
	public:
		ObjectGenerator(int count);

		void OnUpdate(float ts, const CircleProps& props);
		void OnRender(Engine::Graphics::Window* window);

		void Reset();
	private:
		Circle Generate(const CircleProps& props);
		
		std::vector<Circle> m_CirclePool;

		uint32_t m_PoolIndex = 0;
	};

}