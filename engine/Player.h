#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "math.h"
#include "GLpch.h"

#define WIDTH 800
#define HEIGHT 600

class Player { // TODO  : Dela upp player i physics, core & camera
public:
	//physics
	bool CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale);
	void CheckForJump();
	void HandleCollision();

	int jumpcount = 100;
	bool isJump = false, collided, grounded;
	float velocity, dt, lastTime;
	bool movingForward, movingLeft, movingRight, movingBack;

	//camera
	Math::Matrix4 GetView();
	Math::Vector3 position = Math::Vector3(0, 100, 0);
	Math::Vector3 worldUp = Math::Vector3(0, 1, 0);
	Math::Vector3 lForward;
	Math::Vector3 up = Math::Vector3(0, 1, 0);
	Math::Vector3 right;
	float yaw = -90.0f, pitch = 0.0f,sens = 0.11f;
	void UpdateValues();
};