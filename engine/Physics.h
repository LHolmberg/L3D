#pragma once
#include "math.h"
#include <cmath>

class Physics {
public:
	bool CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale);
	bool collided;
	void HandleCollision();
};