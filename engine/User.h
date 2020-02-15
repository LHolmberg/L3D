#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "math.h"

#define WIDTH 1600
#define HEIGHT 900

class Player 
{
public:
	//physics
	bool CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale);
	float UpdateSpeed(float speed);
	void CheckForJump();
	bool grounded;
	int jumpcount = 100, speed = 20;;
	bool isJump = false, collided;
	bool mF, mB, mL, mR;
	bool onTop = false;
	float velocity;
	//camera
	Math::Matrix4 GetView();
	Math::Vector3 position = Math::Vector3(0, 250, 0);
	Math::Vector3 worldUp = Math::Vector3(0, 1, 0);
	Math::Vector3 lForward;
	Math::Vector3 up = Math::Vector3(0, 1, 0);
	Math::Vector3 right;
	float yaw = -90.0f, pitch = 0.0f,sens = 0.11f;
	float dt, lastTime;
	void UpdateValues();
};

class Input : public Player
{
public:
	enum class KeyCode { W, A, S, D, SPACE, ESCAPE};
	bool GetKey(KeyCode k);
	static void RegisterMouseM(GLFWwindow* window, double xPos, double yPos);
	void MoveKeyboard();
	void MoveMouse(float xOffset, float yOffset, bool constraint = true);
	float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0;
	bool firstMouse = true;
};


class Window : public Input  
{
public:
	void SetVersion(int v);
	int Startup(const unsigned int width, const unsigned int height);
	void Update();
	GLFWwindow* window;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};