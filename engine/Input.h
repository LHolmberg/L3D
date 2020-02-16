#pragma once
#include "Player.h"

class Input : public Player {
public:
	enum class KeyCode { W, A, S, D, SPACE, ESCAPE };
	bool GetKey(KeyCode k);
	static void RegisterMouseM(GLFWwindow* window, double xPos, double yPos);
	void MoveKeyboard();
	void MoveMouse(float xOffset, float yOffset, bool constraint = true);
	float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0;
	bool firstMouse = true;
};
