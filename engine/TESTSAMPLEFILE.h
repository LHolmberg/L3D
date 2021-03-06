#pragma once
#include "core.h"

namespace Game {

	L3D::TEXTURE texture1;
	L3D::TEXTURE texture2;

	void Update() {
		engine::Update(); //CORE UPDATE
		// GAME
		
		for (int i = 1; i <= 200 / 10; i++) {
			L3D::CreateCube(Math::Vector3(100 - (i * 10), -5, 100), Math::Vector3(10, 10, 10), texture2);
			L3D::CreateCube(Math::Vector3(100 - (i * 10), -5, -100), Math::Vector3(10, 10, 10), texture2);
			L3D::CreateCube(Math::Vector3(100, -5, 100 - (i * 10)), Math::Vector3(10, 10, 10), texture2);
		}
		
		for (int j = 0; j < 20; j++) {
			for (int i = 0; i < 20; i++)
				L3D::CreateCube(Math::Vector3(100 - (i * 10), -10, 100-(j*10)), Math::Vector3(10, 1, 10), texture1);
		}

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
