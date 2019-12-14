#pragma once
#include <iostream>
#include "Shader.h"
#include "TESTSAMPLEFILE.h"
Window win;
Shader shader;
#define running !glfwWindowShouldClose(win.window)

namespace core
{
	template<typename T>
	void log(T in)
	{
		std::cout << in << std::endl;
	}

	void Startup()
	{
		win.Startup(WIDTH, HEIGHT);
		shader.Startup();
		Game::Startup();
	}

	void Update()
	{
		win.Update();
		shader.Update(win);
		Game::Update();
		glfwPollEvents();
		win.MoveKeyboard();

		glfwSwapBuffers(win.window);
	}

	void Shutdown()
	{
		shader.Shutdown();
		Game::Shutdown();
		glfwTerminate();
	}
}