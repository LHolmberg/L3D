#pragma once
#include <iostream>
#include "GameObject.h"
#include "Cube.h"
#include "Window.h"
#include "Physics.h"
#include "Skybox.h"
#include <assert.h>

Window win;
GameObject go;
Skybox skybox;
Cube cube;
Physics p;

//Simplified user expressions
namespace L3D {
	typedef unsigned int TEXTURE;
	void HandleCollision(bool collided) {
		if (win.movingForward == true && collided == true) {
			win.position.x -= win.lForward.x * (40 * win.dt);
			win.position.z -= win.lForward.z * (40 * win.dt);

		}
		if (win.movingBack == true && collided == true) {
			win.position.x += win.lForward.x * (40 * win.dt);
			win.position.z += win.lForward.z * (40 * win.dt);
		}
		if (win.movingLeft == true && collided == true) {
			win.position.x += win.right.x * (40 * win.dt);
			win.position.z += win.right.z * (40 * win.dt);
		}
		if (win.movingRight == true && collided == true) {
			win.position.x -= win.right.x * (40 * win.dt);
			win.position.z -= win.right.z * (40 * win.dt);
		}
	}
	auto CreateCube(Math::Vector3 position, Math::Vector3 scale, unsigned int texture) {
		HandleCollision(p.CheckCollision(position, win.position, scale));
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