#pragma once

namespace Engine {

	struct ParticleProps
	{
		sf::Vector2f Position;
		sf::Vector2f DirectionRange;
		sf::Vector2i SpeedRandomRangeX{ -5, 5 }, SpeedRandomRangeY{ -5, 5 };
		sf::Color ColorBegin, ColorEnd;
		int Speed, ColorCnageStep = 1;
		float SizeBegin, SizeEnd;
		float LifeTime = 1.0f;
	};

	struct Particle
	{
		sf::Vector2f Position;
		sf::Vector2f Speed;
		sf::Color ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;
		int ColorCnageStep = 1;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		sf::RectangleShape ParticleShape;

		bool Active = false;
	};


	class ParticleSystem
	{
	public:
		ParticleSystem();

		void OnUpdate(float ts, sf::Vector2f speed = sf::Vector2f(0.0f, 0.0f));
		void OnRender(Engine::Graphics::Window* window);

		void Emit(const ParticleProps& particleProps);

		void Reset();
	private:

		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 0;
	};
}