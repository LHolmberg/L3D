#include "Shader.h"

Window win;
Shader shader;

int main() 
{
	win.Startup(WIDTH,HEIGHT);
	shader.Startup();

	while (running)
	{
		win.Update();
		shader.Update(win);

		glfwPollEvents();
		win.MoveKeyboard();

		glfwSwapBuffers(win.window);
	}

	shader.Shutdown();
	glfwTerminate();

	return 0;
}