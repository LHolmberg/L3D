#include "GameObject.h"

void GameObject::Startup() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

unsigned int GameObject::CreateShader(std::string vShader, std::string fShader) {
	std::string vContent;
	std::ifstream vStream(vShader, std::ios::in);

	if (!vStream.is_open()) {
		std::cout << "ERROR - > " << vShader;
		return 0;
	}

	std::string vLine = "";
	while (!vStream.eof()) {
		std::getline(vStream, vLine);
		vContent.append(vLine + "\n");
	}

	vStream.close();

	std::string fContent;
	std::ifstream fStream(fShader, std::ios::in);

	if (!fStream.is_open()) {
		std::cout << "ERROR - > " << fShader;
		return 0;
	}

	std::string fLine = "";
	while (!fStream.eof()) {
		std::getline(fStream, fLine);
		fContent.append(fLine + "\n");
	}

	fStream.close();

	const char* vertexCode = vContent.c_str();
	const char* fragmentCode = fContent.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, 0);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, 0);
	glCompileShader(fragment);

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

unsigned int GameObject::LoadCubemap(const char* list[]) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < 6; i++) {
		image = SOIL_load_image(list[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}