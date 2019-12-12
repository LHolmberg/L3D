#pragma once
#include <iostream>

#define running !glfwWindowShouldClose(win.window)

namespace core
{
	template<typename T>
	void log(T in)
	{
		std::cout << in << std::endl;
	}
}