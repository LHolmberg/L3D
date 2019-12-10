#include "Random.h"

int Random::Range(int x, int y)
{
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(x, y); // distribution in range [1, 6]

	return dist6(rng);
}