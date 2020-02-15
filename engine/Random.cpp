#include "Random.h"

int Random::Range(int x, int y)
{
	std::mt19937 rng(d());
	std::uniform_int_distribution<std::mt19937::result_type> num(x, y); // distribution in range [1, 6]

	return num(rng);
}