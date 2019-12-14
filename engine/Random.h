#pragma once
#include <iostream>
#include <random>

class Random
{
public:
	std::random_device d;
	int Range(int x, int y);
};