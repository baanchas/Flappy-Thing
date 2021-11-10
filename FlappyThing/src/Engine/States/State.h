#pragma once

namespace Engine {

	class State
	{
	public:
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(sf::Event& e) = 0;
	private:
	};

}