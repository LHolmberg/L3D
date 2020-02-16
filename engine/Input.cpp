#include "Input.h"

bool Input::GetKey(KeyCode k) {
	switch (k) {
	case KeyCode::W: return GETKEY(K_W) == 1 ? true : false;
	case KeyCode::A: return GETKEY(K_A) == 1 ? true : false;
	case KeyCode::S: return GETKEY(K_S) == 1 ? true : false;
	case KeyCode::D: return GETKEY(K_D) == 1 ? true : false;
	case KeyCode::ESCAPE: return GETKEY(K_ESC) == 1 ? true : false;
	case KeyCode::SPACE: return GETKEY(K_SPACE) == 1 ? true : false;
	default: return false;
	}
}

void Input::MoveKeyboard() {
	float curTime = glfwGetTime();
	dt = curTime - lastTime;

	float newVel = 40 * dt;
	lastTime = curTime;

	if (GetKey(KeyCode::W) == true) {
		position.x += lForward.x * newVel;
		position.z += lForward.z * newVel;
		movingForward = true;
	}
	else
		movingForward = false;

	if (GetKey(KeyCode::S) == true) {
		position.x -= lForward.x * newVel;
		position.z -= lForward.z * newVel;
		movingBack = true;
	}
	else
		movingBack = false;

	if (GetKey(KeyCode::A) == true) {
		position.x -= right.x * newVel;
		position.z -= right.z * newVel;
		movingLeft = true;
	}
	else
		movingLeft = false;

	if (GetKey(KeyCode::D) == true) {
		position.x += right.x * newVel;
		position.z += right.z * newVel;
		movingRight = true;
	}
	else
		movingRight = false;

	if (GetKey(KeyCode::ESCAPE) == true)
		EXIT;

	if (GetKey(KeyCode::SPACE) == true) {
		if (grounded == true)
			isJump = true;
	}
}


void Input::MoveMouse(float xOffset, float yOffset, bool constraint) {
	xOffset *= sens;
	yOffset *= sens;
	yaw += xOffset;
	pitch += yOffset;

	if (constraint) {
		if (pitch > 89)
			pitch = 89;

		if (pitch < -89)
			pitch = -89;
	}

	this->UpdateValues();
}

void Input::RegisterMouseM(GLFWwindow* window, double xPos, double yPos) {
	Input* staticRef = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (staticRef->firstMouse) {
		staticRef->lastX = xPos;
		staticRef->lastY = yPos;
		staticRef->firstMouse = false;
	}

	float xOffset = xPos - staticRef->lastX;
	float yOffset = staticRef->lastY - yPos;

	staticRef->lastX = xPos;
	staticRef->lastY = yPos;

	staticRef->MoveMouse(xOffset, yOffset);
}
