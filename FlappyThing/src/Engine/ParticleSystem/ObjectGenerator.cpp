#include "ftpch.h"
#include "ObjectGenerator.h"
#include "Engine/Random.h"

namespace Engine {

	ObjectGenerator::ObjectGenerator(int count)
	{
		m_CirclePool.resize(count);

		// set position out of range to start genretae objects

		for (auto& circle : m_CirclePool)
		{
			circle.Position.x = -55;
			circle.Position.y = 741;
		}
	}

	void ObjectGenerator::OnUpdate(float ts, const CircleProps& props)
	{
		for (auto& circle : m_CirclePool)
		{
			circle.Time -= ts;

			if (circle.Time < 0)
			{
				circle.Position += circle.Speed * ts;
				circle.ShapeCircle.setPosition(circle.Position);
			}

			if (circle.Position.x < -50 || circle.Position.y > 740)
			{
				circle = Generate(props);
			}
		}
	}

	void ObjectGenerator::OnRender(Engine::Graphics::Window* window)
	{
		for (auto& circle : m_CirclePool)
		{
			window->Render(circle.ShapeCircle);
		}
	}

	Circle ObjectGenerator::Generate(const CircleProps& props)
	{
		// set object with random parameters

		Circle circle;

		circle.Time = Random::RangedRandom(props.Time.x, props.Time.y);

		circle.Position.x = Random::RangedRandom(props.PositionX.x, props.PositionX.y);
		circle.Position.y = Random::RangedRandom(props.PositionY.x, props.PositionY.y);
		circle.ShapeCircle.setPosition(circle.Position);
		circle.ShapeCircle.setRadius(Random::RangedRandom(props.Radius.x, props.Radius.y));

		circle.Speed.x = Random::RangedRandom(props.SpeedRandomRangeX.x, props.SpeedRandomRangeX.y);
		circle.Speed.y = Random::RangedRandom(props.SpeedRandomRangeY.x, props.SpeedRandomRangeY.y);

		circle.ShapeCircle.setFillColor(sf::Color::Yellow);

		return circle;
	}

	void ObjectGenerator::Reset()
	{
		for (auto& circle : m_CirclePool)
		{
			circle.Position.x = -55;
			circle.Position.y = 741;
		}
	}
}