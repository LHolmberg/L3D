#include "Ai.h"

namespace AI
{

	int StateMachine::AddState(std::string name, void* func)
	{
		if (states.find(name) != states.end())
		{
			return 0;
		}
		else
		{
			std::pair<std::string, void*>pair(name, func);
			states.insert(pair);
			return -1;
		}
	}

	int StateMachine::SetActiveState(std::string name, void* func)
	{

		if (states.find(name) != states.end())
		{
			activeState = func;
			return 0;
		}
		else
			return -1;
	}

	int StateMachine::Run(void* func)
	{
		if (activeState == NULL)
		{
			return -1;
		}
		else
		{
			activeState = func;
			return 0;
		}

	}

	void StateMachine::Reset()
	{
		activeState = NULL;
	}
}