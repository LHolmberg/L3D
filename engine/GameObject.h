#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "User.h"
#include "Random.h"
#include "math.h"
#include "GLpch.h"

#include "external/SOIL/stb_image_aug.h"
#include <soil.h>


class GameObject {
public:
	void Startup();

	unsigned int CreateShader(std::string vShader, std::string fShader);
	unsigned int program;

	unsigned int cubemapTexture;
	static unsigned int LoadCubemap(const char* list[]);

	const float* viewPtr;
	const float* projPtr;

	Math::Matrix4 view;
	Math::Matrix4 projection;
	Math::Matrix4 model;
};