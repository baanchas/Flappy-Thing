#include "ftpch.h"
#include "StateManager.h"


namespace Engine {

	void StateManager::PushState(State* state)
	{
		m_States.push(state);
	}

	State* StateManager::GetTop()
	{
		return m_States.top();
	}

	void StateManager::Pop()
	{
		m_States.pop();
	}

}