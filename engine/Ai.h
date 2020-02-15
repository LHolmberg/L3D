#pragma once
#include <iostream>
#include <map>

namespace AI
{
	typedef struct StateMachine {
		std::map<std::string, void*>states;

		void* activeState = NULL;

		int AddState(std::string name, void* func);
		int SetActiveState(std::string name, void* func);
		int Run(void* func);
		void Reset();
	} StateMachine;
}
