#include "ftpch.h"

#include "ParticleSystem.h"

namespace Engine {

	ParticleSystem::ParticleSystem()
	{
		m_ParticlePool.resize(500);
	}

	void ParticleSystem::OnUpdate(float ts, sf::Vector2f speed)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.ParticleShape.setFillColor(particle.ColorBegin);
			particle.ParticleShape.setPosition(particle.Position);
			particle.ParticleShape.setRotation(particle.Rotation);

			// Change transform and Lifetime ratio that passed

			particle.LifeRemaining -= ts;
			particle.Position += particle.Speed * (float)ts + speed;
			particle.Rotation += 10 * ts;

			float r, g, b;

			// Change particle color from begin color to ending color

			if (particle.ColorBegin.r > particle.ColorEnd.r)
				particle.ColorBegin.r -= particle.ColorCnageStep;
			else
				particle.ColorBegin.r += particle.ColorCnageStep;

			if (particle.ColorBegin.g > particle.ColorEnd.g)
				particle.ColorBegin.g -= particle.ColorCnageStep;
			else
				particle.ColorBegin.g += particle.ColorCnageStep;

			if (particle.ColorBegin.b > particle.ColorEnd.b)
				particle.ColorBegin.b -= particle.ColorCnageStep;
			else
				particle.ColorBegin.b += particle.ColorCnageStep;

			// making disappear particle

			float life = particle.LifeRemaining / particle.LifeTime;
			particle.ColorBegin.a = particle.ColorBegin.a * life;
		}
	}

	void ParticleSystem::OnRender(Engine::Graphics::Window* window)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			window->Render(particle.ParticleShape);
		}
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps)
	{
		// set particle properties

		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position = particleProps.Position;
		particle.Rotation = Random::RangedRandom(0, 90);

		particle.ParticleShape.setSize(sf::Vector2f( 10.0f, 10.0f));
		particle. ParticleShape.setOrigin(particle.ParticleShape.getSize().x / 2, particle.ParticleShape.getSize().y / 2);

		particle.Speed.x = Random::RangedRandom(particleProps.SpeedRandomRangeX.x, particleProps.SpeedRandomRangeX.y) * particleProps.Speed;
		particle.Speed.y = Random::RangedRandom(particleProps.SpeedRandomRangeY.x, particleProps.SpeedRandomRangeY.y) * particleProps.Speed;

		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;

		particle.LifeTime = particleProps.LifeTime;
		particle.LifeRemaining = particleProps.LifeTime;
		particle.SizeEnd = particleProps.SizeEnd;
		particle.ColorCnageStep = particleProps.ColorCnageStep;


		m_PoolIndex++;

		if (m_PoolIndex == 499)
		{
			m_PoolIndex = 0;
		}
	}

	void ParticleSystem::Reset()
	{
		for (auto& element : m_ParticlePool)
		{
			element.Active = false;
		}
	}
}