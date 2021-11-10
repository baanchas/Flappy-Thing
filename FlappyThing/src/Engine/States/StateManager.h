#pragma once

#include "State.h"

namespace Engine {

	class StateManager
	{
	public:

		void PushState(State* state);
		State* GetTop();
		void Pop();

	private:
		std::stack<State*> m_States;
	};

}