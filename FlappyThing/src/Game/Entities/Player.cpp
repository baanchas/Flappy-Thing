#include "ftpch.h"
#include "Player.h"


#include "App.h"


namespace Game {

	Player::Player()
	{
		m_Position = sf::Vector2f(Engine::Application::Get()->GetWindow()->GetWidth() / 2, 200.0f);
		m_Rotation = 90.0f;
		
		m_Vertices.resize(8);

		InitSprite();

		InitCollider();

		InitSound();

		// smoke properties
		{
			m_SmokeProps.ColorBegin = sf::Color(150, 150, 150, 255);
			m_SmokeProps.ColorEnd = sf::Color(70, 70, 70, 255);
			m_SmokeProps.LifeTime = 20.0f;
			m_SmokeProps.Speed = 10.0f;
			m_SmokeProps.ColorCnageStep = 5;
		}
	}

	void Player::OnUpdate(float ts)
	{
		// make fall player permanently
		Move(sf::Vector2f(0.0f, m_SpeedY * ts));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			AnimateFlying();
		}

		// play engine sound while bouncing
		PlaySounds();

		// emit sparks while bouncing 
		EmitSparks();

		// set rotation to default
		if (m_Rotation < MAX_ROTATION)
		{
			m_Rotation += 3.0f;
		}

		// set speed to MAX permanently
		if (m_SpeedY < MAX_SPEED)
		{
			m_SpeedY += 25.0f;
		}

		// set position and rottaion of sprite and box collider
		SetTransformation();

		// compute vetices cooedinates of sprite
		ComputeCoordinates();

		UpdateSmoke(ts, sf::Vector2f(-6.0f, 0.0f));
	}

	void Player::OnEvent(sf::Event& e)
	{
		// set up speed of the Player to the Max

		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				m_SpeedY = -MAX_SPEED;
			}
		}

		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				
				m_SpeedY = -MAX_SPEED;
			}
		}
	}

	void Player::Render(Engine::Graphics::Window* window)
	{
		m_Smoke.OnRender(window);
	
		window->Render(m_RocketSprite);
	}

	void Player::InitSprite()
	{
		m_RocketTexture.loadFromFile("res/sprites/rocket/rocket.png");
		m_RocketTexture.setSmooth(true);
		m_RocketSprite.setTexture(m_RocketTexture);
		m_RocketSprite.setScale(1.2f, 1.2f);
		m_RocketSprite.setOrigin((float)m_RocketTexture.getSize().x / 2, (float)m_RocketTexture.getSize().y / 2);
	}

	void Player::InitCollider()
	{
		m_BoxCollider.setSize(COLLIDER_SIZE);
		m_BoxCollider.setOrigin(COLLIDER_SIZE.x / 2, COLLIDER_SIZE.y / 2);
		m_BoxCollider.setFillColor(sf::Color(1, 1, 1, 0));
		m_BoxCollider.setOutlineColor(sf::Color(255, 0, 0, 255));
		m_BoxCollider.setOutlineThickness(1);
	}

	void Player::InitSound()
	{
		m_SoundBuffer.loadFromFile("res/sound/rocket.wav");
		m_RocketSound.setBuffer(m_SoundBuffer);
		m_RocketSound.setVolume(0);
		m_RocketSound.setLoop(true);
		m_RocketSound.play();
	}

	void Player::AnimateFlying()
	{
		// animate sprite consider to speed

		if (m_SpeedY < 0)
		{
			if (m_Rotation > 30)
			{
				if (m_Rotation > 90.0f)
				{
					m_Rotation = 90.0f;
				}

				m_Rotation -= 10.0f;
			}
		}
	}

	void Player::UpdateSmoke(float ts, sf::Vector2f speed)
	{
		m_SmokeProps.Position = sf::Vector2f(GetVerticesCoordinates()[4].x, GetVerticesCoordinates()[4].y);

		for (int i = 0; i < 6; i++)
		{
			m_Smoke.Emit(m_SmokeProps);
		}

		m_Smoke.OnUpdate(ts, speed);
	}

	// Play engine while bouncing 

	void Player::PlaySounds()
	{
		if (m_SpeedY < 0)
		{
			if (IsAlive())
			{
				SetVolume(70);
			}
		}
		else if (m_SpeedY > 0)
		{
			SetVolume(0);
		}
	}

	// Emit sparks while bouncing 

	void Player::EmitSparks()
	{
		if (m_SpeedY < 0)
		{
			m_SmokeProps.ColorBegin = sf::Color(250, 0, 0, 255);
			m_SmokeProps.ColorCnageStep = 30;
		}
		else if (m_SpeedY > 0)
		{
			m_SmokeProps.ColorBegin = sf::Color(150, 150, 150, 255);
			m_SmokeProps.ColorCnageStep = 5;
		}
	}
	
	void Player::SetVolume(int voluume)
	{
		m_RocketSound.setVolume(voluume);
	}

	// Reset Player to default condition

	void Player::Reset()
	{
		m_Smoke.Reset();
		m_Position = sf::Vector2f((float)Engine::Application::Get()->GetWindow()->GetWidth() / 2, (float)Engine::Application::Get()->GetWindow()->GetHeight() / 2);
		m_SpeedY = MAX_SPEED;
		m_Rotation = 90.0f;
		m_IsAlive = true;
	}

	// Compute coordinates of PLayer sprite vertices 

	void Player::ComputeCoordinates()
	{
		float tempX = m_BoxCollider.getSize().x / (float)2;
		float tempY = m_BoxCollider.getSize().y / (float)2;

		float cosMiltiplaier = cos(GetRotation() * (3.141592653589793238463f / 180.0f));
		float sinMiltiplaier = sin(GetRotation() * (3.141592653589793238463f / 180.0f));

		m_Vertices[0].x = (-tempX * cosMiltiplaier - tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[0].y = (-tempX * sinMiltiplaier + tempY * cosMiltiplaier) + GetPosition().y;

		m_Vertices[1].x = (tempX * cosMiltiplaier - tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[1].y = (tempX * sinMiltiplaier + tempY * cosMiltiplaier) + GetPosition().y;

		m_Vertices[2].x = (tempX * cosMiltiplaier - -tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[2].y = (tempX * sinMiltiplaier + -tempY * cosMiltiplaier) + GetPosition().y;

		m_Vertices[3].x = (-tempX * cosMiltiplaier - -tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[3].y = (-tempX * sinMiltiplaier + -tempY * cosMiltiplaier) + GetPosition().y;

		m_Vertices[4].x = (m_Vertices[0].x + m_Vertices[1].x) / 2;
		m_Vertices[4].y = (m_Vertices[0].y + m_Vertices[1].y) / 2;

		m_Vertices[5].x = (m_Vertices[1].x + m_Vertices[2].x) / 2;
		m_Vertices[5].y = (m_Vertices[1].y + m_Vertices[2].y) / 2;

		m_Vertices[6].x = (m_Vertices[2].x + m_Vertices[3].x) / 2;
		m_Vertices[6].y = (m_Vertices[2].y + m_Vertices[3].y) / 2;

		m_Vertices[7].x = (m_Vertices[3].x + m_Vertices[0].x) / 2;
		m_Vertices[7].y = (m_Vertices[3].y + m_Vertices[0].y) / 2;

		tempY = (m_BoxCollider.getSize().y - 15.0) / (float)2;

		m_Vertices[0].x = (tempX * cosMiltiplaier - -tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[0].y = (tempX * sinMiltiplaier + -tempY * cosMiltiplaier) + GetPosition().y;

		m_Vertices[1].x = (-tempX * cosMiltiplaier - -tempY * sinMiltiplaier) + GetPosition().x;
		m_Vertices[1].y = (-tempX * sinMiltiplaier + -tempY * cosMiltiplaier) + GetPosition().y;

	}

	// Set position and rottaion of sprite and box collider

	void Player::SetTransformation()
	{
		m_RocketSprite.setPosition(m_Position);
		m_RocketSprite.setRotation(m_Rotation);

		m_BoxCollider.setPosition(m_Position);
		m_BoxCollider.setRotation(m_Rotation);
	}

}