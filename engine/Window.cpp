#include "Window.h"

void Window::SetVersion(int v) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
}

int Window::Startup(const unsigned int width, const unsigned int height) { //setup window w.h.o glfw/glew
	glfwInit();

	SetVersion(3);

	window = glfwCreateWindow(width, height, "L3D", 0, 0);

	if (!window) {
		std::cout << "glfw init fail" << std::endl;
		glfwTerminate();

		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, RegisterMouseM);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = 1;

	if (glewInit() != 0) {
		std::cout << "glew init fail" << std::endl;

		return 0;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetWindowUserPointer(window, this);
}

void Window::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	HandleCollision();

	CheckForJump();
}