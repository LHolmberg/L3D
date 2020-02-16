#pragma once
#include <iostream>
#include "GameObject.h"
#include "Cube.h"
#include "Skybox.h"
#include <assert.h>

Window win;
GameObject go;
Skybox skybox;
Cube cube;

//Simplified user expressions
namespace L3D {
	typedef unsigned int TEXTURE;

	auto CreateCube(Math::Vector3 position, Math::Vector3 scale, unsigned int texture) {
		return cube.Instantiate(position, scale, texture);
	}

	auto CreateTexture(const char* filename) {
		return cube.Initialize(filename);
	}
}

// Core setup/update
namespace engine {
	void Startup() {
		win.Startup(WIDTH, HEIGHT);
		go.Startup();
		cube.Startup();
		skybox.Startup();
	}

	void Update() {
		win.Update();
		cube.Render(win);
		skybox.Render(win);
		glfwPollEvents();
		win.MoveKeyboard();
	}

	void Shutdown() {
		skybox.Shutdown();
		glfwTerminate();
	}
}