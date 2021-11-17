#pragma once

#include "State.h"

namespace Engine {

	class StateManager
	{
	public:

		void PushState(State* state);
		void Pop();
		State* GetTop();

		int GetSize() { return (int)m_States.size(); }

	private:
		std::stack<State*> m_States;
	};

}