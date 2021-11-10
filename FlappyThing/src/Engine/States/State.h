#pragma once

#include "Graphics/Window.h"

namespace Engine {

	class State
	{
	public:
		virtual bool Exit() { return m_isQuit; };
		virtual void SetAvtive() { m_isQuit = false; }
		
		virtual void OnUpdate(float ts) = 0;
		virtual void OnEvent(sf::Event& e) = 0;
		virtual void OnRender(Graphics::Window* window) = 0;

	protected:
		bool m_isQuit = false;

	private:

		
	};

}