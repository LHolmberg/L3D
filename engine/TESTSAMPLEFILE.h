#pragma once
#include <iostream>
#include "core.h"

namespace Se
{
	Shader sha;
	void Update()
	{
		sha.InstantiateCube(Math::Vector3(0, -10, 0), Math::Vector3(200, 1, 200), sha.textures[1]);
	}

	void Startup()
	{
	}

	void Shutdown()
	{
		std::cout << "hello";
	}
}
