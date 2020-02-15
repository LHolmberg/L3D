#pragma once
#include <iostream>
#include "GameObject.h"
#include "Cube.h"
#include "Skybox.h"

namespace core {
	Window win;
	GameObject go;
	Skybox skybox;
	Cube cube;

	template<typename T>
	void log(T in) {
		std::cout << in << std::endl;
	}

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

		glfwSwapBuffers(win.window);
	}

	void Shutdown() {
		skybox.Shutdown();

		glfwTerminate();
	}
}