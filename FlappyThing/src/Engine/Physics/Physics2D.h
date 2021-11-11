#pragma once

#include "ftpch.h"

namespace Engine {	namespace Physics {

	class Physics2D
	{
	public:
		static void Move(sf::Vector2f& vector, sf::Vector2f inc)
		{
			vector += inc;
		}
	};

}}