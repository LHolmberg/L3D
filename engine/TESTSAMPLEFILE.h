#pragma once
#include <iostream>
#include "core.h"



namespace Game {

	void Update() {
		core::Update(); //CORE UPDATE
		//GAME
	}

	void Startup() {
		core::Startup(); //CORE STARTUP
		//GAME
		
	}

	//on exit
	void Shutdown() {
		core::Shutdown(); //CORE SHUTDOWN
		//GAME

	}
}
