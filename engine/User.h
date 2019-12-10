#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "math.h"
#include "core.h"

#define WIDTH 1600
#define HEIGHT 900

class User
{
public:
	//window
	void SetVersion(int v);
	int Startup(const unsigned int width, const unsigned int height);
	void Update();
	GLFWwindow* window;
	int SCREEN_WIDTH, SCREEN_HEIGHT;


	//input
	static void RegisterMouseM(GLFWwindow* window, double xPos, double yPos);
	void MoveKeyboard();
	void MoveMouse(float xOffset, float yOffset, bool constraint = true);
	float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0;
	bool firstMouse = true;

	//physics
	bool CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale);
	float UpdateSpeed(float speed);
	bool grounded;
	int jumpcount = 100;
	bool isJump = false;
	bool collided;
	bool mF, mB, mL, mR;
	bool onTop = false;
	void CheckForJump();
	int speed = 20;


	//camera
	Math::Matrix4 GetView();
	Math::Vector3 pPos = Math::Vector3(0, 250, 0);
	Math::Vector3 worldUp = Math::Vector3(0, 1, 0);
	Math::Vector3 lForward;
	Math::Vector3 up = Math::Vector3(0, 1, 0);
	Math::Vector3 right;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float sens = 0.11f;
	float dt, lastTime;
	void UpdateValues();
};

