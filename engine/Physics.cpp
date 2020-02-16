#include "Physics.h"

bool Physics::CheckCollision(Math::Vector3 a, Math::Vector3 b, Math::Vector3 scale) {
	if (abs(a.x - b.x) < scale.x) {
		if (abs(a.y - b.y) < scale.y) {
			if (abs(a.z - b.z) < scale.z)
				return true;
		}
	}
	return false;
}


