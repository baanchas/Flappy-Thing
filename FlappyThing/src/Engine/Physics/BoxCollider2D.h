#pragma once 

namespace Engine {	namespace Physics {

	class BoxCollider2D
	{
	public:
		sf::Vector2f Offset = { 0.0f, 0.0f };
		sf::Vector2f Size = { 0.5f, 0.5f };

		float Dencity = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionTreshold = 0.5f;

		void* RuntimeFixture = nullptr;
	private:

	};

}}