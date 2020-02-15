#include "User.h"

void Window::SetVersion(int v) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
}

int Window::Startup(const unsigned int width, const unsigned int height) { //setup window w.h.o glfw/glew
	glfwInit();

	SetVersion(3);

	window = glfwCreateWindow(width, height, "L3D", nullptr, nullptr);

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

bool Player::CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale) {
	if (abs(a.x - b.x) < scale.x) {
		if (abs(a.y - b.y) < scale.y) {
			if (abs(a.z - b.z) < scale.z)
				return true;
		}
	}
	return false;
}

bool Input::GetKey(KeyCode k) {
	switch (k) {
		case KeyCode::W: return GETKEY(GLFW_KEY_W) == 1 ? true : false;
		case KeyCode::A: return GETKEY(GLFW_KEY_A) == 1 ? true : false;
		case KeyCode::S: return GETKEY(GLFW_KEY_S) == 1 ? true : false;
		case KeyCode::D: return GETKEY(GLFW_KEY_D) == 1 ? true : false;
		case KeyCode::ESCAPE: return GETKEY(GLFW_KEY_ESCAPE) == 1 ? true : false;
		case KeyCode::SPACE: return GETKEY(GLFW_KEY_SPACE) == 1 ? true : false;
		default: return false;
	}
}

void Input::MoveKeyboard() {
	float curTime = glfwGetTime();
	dt = curTime - lastTime;

	float newVel = UpdateSpeed(20) * dt;
	lastTime = curTime;

	if (GetKey(KeyCode::W) == true) {
		position.x += lForward.x * newVel;
		position.z += lForward.z * newVel;
	}

	if (GetKey(KeyCode::S) == true) {
		position.x -= lForward.x * newVel;
		position.z -= lForward.z * newVel;
	}

	if (GetKey(KeyCode::A) == true) {
		position.x -= right.x * velocity;
		position.z -= right.z * velocity;
	}

	if (GetKey(KeyCode::D) == true) {
		position.x += right.x * velocity;
		position.z += right.z * velocity;
	}

	if (GetKey(KeyCode::ESCAPE) == true)
		EXIT;

	if (GetKey(KeyCode::SPACE) == true) {
		if (grounded == true)
			isJump = true;
	}
}

void Player::HandleCollision() {
	if (CheckCollision(position, Math::Vector3(0, -10, 0), Math::Vector3(100, 5, 100)) != true && collided != true) { // Gravity, pull down
		grounded = false;
		position.y -= 50 * dt;
	}
	else
		grounded = true;
}

void Player::CheckForJump() {
	if (isJump == true)  {
		if (jumpcount >= 0) {
			position.y += (jumpcount) * 0.01;
			jumpcount -= 1;
		}
		else {
			jumpcount = 100;
			isJump = false;
		}
	}
}

float Player::UpdateSpeed(float speed) { //Temporary fix for look down=slowmovement GOTTA GO
	if (abs(pitch) > 48 && abs(pitch) < 57)
		return speed + 7;
	else if (abs(pitch) > 57 && abs(pitch) < 65)
		return speed + 19;
	else if (abs(pitch) > 65 && abs(pitch) < 70)
		return speed + 38;
	else if (abs(pitch) > 70 && abs(pitch) < 75)
		return speed + 49;
	else if (abs(pitch) > 75 && abs(pitch) < 80)
		return speed + 77;
	else if (abs(pitch) > 80 && abs(pitch) < 83)
		return speed + 129;
	else if (abs(pitch) > 83 && abs(pitch) < 85)
		return speed + 218;
	else if (abs(pitch) > 85 && abs(pitch) < 87.6f)
		return speed + 266;
	else if (abs(pitch) > 87.6f && abs(pitch) < 88.5f)
		return speed + 280;
	else if (abs(pitch) > 88.5f)
		return speed + 1000;
	else
		return 20;
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


Math::Matrix4 Player::GetView() {
	return Math::lookAt(position, position + lForward, worldUp);
}


void Player::UpdateValues() {
	Math::Vector3 front;

	front.x = cos(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
	front.y = sin(Math::ToRadians(pitch));
	front.z = sin(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
	lForward = Math::Normalize(front);

	right = Math::Normalize(Math::Crossproduct(lForward, worldUp));
	up = Math::Normalize(Math::Crossproduct(right, lForward));
}