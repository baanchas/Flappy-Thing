#include "ftpch.h"
#include "Entity.h"


namespace Engine {

	void Entity::Move(const sf::Vector2f& vector)
	{
		m_Position += vector;
	}

	void Entity::SetPosition(const sf::Vector2f& vector)
	{
		m_Position = vector;
	}

	void Entity::SetRotation(const float& rotation)
	{
		m_Rotation = rotation;
	}

}