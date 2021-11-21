#pragma once

#include "Engine/Entity/Entity.h"
#include "Engine/ParticleSystem/ParticleSystem.h"

namespace Game {

	class Player : public Engine::Entity
	{
	public:

		Player();
		~Player() {};


		void OnUpdate(float ts) override;
		void OnEvent(sf::Event& e) override;
		void Render(Engine::Graphics::Window* window) override;

		void InitSprite();
		void InitCollider();
		void InitSound();

		void UpdateSmoke(float ts, sf::Vector2f speed);

		void AnimateFlying();

		void SetTransformation();
		void ComputeCoordinates();
		void SetVitality(bool alive) { m_IsAlive = alive; };

		void EmitSparks();
		void PlaySounds();
		void SetVolume(int volume);

		void Reset();


		std::vector<sf::Vector2f>& GetVerticesCoordinates() { return m_Vertices; };
		sf::Vector2u GetSize() { return m_RocketTexture.getSize(); }
		inline bool IsAlive() { return m_IsAlive; }
		
	public:
		Engine::ParticleProps m_SmokeProps;
	private:

	private:
		bool m_IsAlive = true;
		
		std::vector<sf::Vector2f> m_Vertices;

		sf::SoundBuffer m_SoundBuffer;
		sf::Sound m_RocketSound;

		sf::Texture m_RocketTexture;
		sf::Sprite m_RocketSprite;
		
		sf::RectangleShape m_BoxCollider;
		sf::RectangleShape m_BoxColliderHead;

		Engine::ParticleSystem m_Smoke;

		float m_SpeedY = 400.0f;

		// constants

		const sf::Vector2f COLLIDER_SIZE = {26.0f, 50.0f};

		const float JUMP_SPEED = 500.0f;
		const float MAX_SPEED = 500.0f;
		
		const float MAX_ROTATION = 150.0f;

	};

}