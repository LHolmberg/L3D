#include "Player.h"

bool Player::CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale) {
	if (abs(a.x - b.x) < scale.x) {
		if (abs(a.y - b.y) < scale.y) {
			if (abs(a.z - b.z) < scale.z)
				return true;
		}
	}
	return false;
}


void Player::HandleCollision() {
	if (CheckCollision(position, Math::Vector3(0, -5, 0), Math::Vector3(100, 5, 100)) != true && collided != true) { // Gravity, pull down
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