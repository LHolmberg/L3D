#include "Shader.h"

User usr;
Shader shader;

int main() 
{
	usr.Startup(WIDTH,HEIGHT);
	shader.Startup();

	while (running)
	{
		usr.Update();
		shader.Update(usr);

		glfwPollEvents();
		usr.MoveKeyboard();

		glfwSwapBuffers(usr.window);
	}

	shader.Shutdown();
	glfwTerminate();

	return 0;
}