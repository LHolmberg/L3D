#pragma once
#include "Input.h"

class Window : public Input {
public:
	void SetVersion(int v);
	int Startup(const unsigned int width, const unsigned int height);
	void Update();
	GLFWwindow* window;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};