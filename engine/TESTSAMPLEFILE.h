#pragma once
#include "core.h"

namespace Game {

	L3D::TEXTURE texture1;
	L3D::TEXTURE texture2;

	void Update() {
		engine::Update(); //CORE UPDATE
		// GAME
		
		L3D::CreateCube(Math::Vector3(2, -5, 10), Math::Vector3(5, 24, 5), texture2);
		L3D::CreateCube(Math::Vector3(10, -5, 20), Math::Vector3(5, 5, 5), texture2);
		L3D::CreateCube(Math::Vector3(0, -10, 0), Math::Vector3(200, 1, 200), texture1);



		SWAP_BUFFERS;
	}

	void Startup() {
		engine::Startup(); //CORE STARTUP
		//GAME
		texture1 = L3D::CreateTexture("engine/resources/images/Png.png");
		texture2 = L3D::CreateTexture("engine/resources/images/s.jpg");
	}

	//on exit
	void Shutdown() {
		engine::Shutdown(); //CORE SHUTDOWN
		//GAME

	}
}
