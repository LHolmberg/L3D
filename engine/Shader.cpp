#include "Shader.h"

void Shader::InstantiateCube(Math::Vector3 pos, Math::Vector3 scale, unsigned int texture)
{
	glUseProgram(cube);
	void* mPtr = &model;
	const float* modelPtr = (float*)mPtr;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(cube, "ourTexture1"), 0);

	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(cube, "model");
	GLint viewLoc = glGetUniformLocation(cube, "view");
	GLint projLoc = glGetUniformLocation(cube, "projection");

	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewPtr);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, projPtr);

	glBindVertexArray(VAO);

	model = Math::Translate(pos);
	model.m[0][0] = scale.x; // scaling, tempfix
	model.m[1][1] = scale.y;
	model.m[2][2] = scale.z;
	model.m[3][3] = 1;

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelPtr);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Shader::Update(User usr)
{

	//SETUP
	Math::Matrix4 projection = Math::Perspective(60.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);
	Math::Matrix4 view = usr.GetView();
	Math::Matrix4 model;
	void* vPtr = &view;
	viewPtr = (float*)vPtr;

	void* pPtr = &projection;
	projPtr = (float*)pPtr;

	InstantiateCube(Math::Vector3(2, -5, 10), Math::Vector3(5, 5, 5), textures[0]);
	InstantiateCube(Math::Vector3(10, -5, 20), Math::Vector3(5, 5, 5), textures[0]);
	InstantiateCube(Math::Vector3(0, -10, 0), Math::Vector3(200, 1, 200), textures[1]);
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Y) == 1)
		InstantiateCube(Math::Vector3(random.Range(0,40), -5, random.Range(0, 40)), Math::Vector3(5, 5, 5), textures[0]);
	//SKYBOX
	glDepthFunc(GL_LEQUAL);
	glUseProgram(sky);

	view = Math::To3x3((usr.GetView()));
	glUniformMatrix4fv(glGetUniformLocation(sky, "view"), 1, GL_FALSE, viewPtr);
	glUniformMatrix4fv(glGetUniformLocation(sky, "projection"), 1, GL_FALSE, projPtr);
	glBindVertexArray(skyVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void Shader::InitializeCube(const char* path)
{
	unsigned int texture;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures.push_back(texture);
}

void Shader::Startup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cube = CreateShader("engine/shaders/core.vs", "engine/shaders/core.frag");
	sky = CreateShader("engine/shaders/skybox.vs", "engine/shaders/skybox.frag");

	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);


	const char* list[6] = {

		"engine/cubemaps/right.bmp",
		"engine/cubemaps/left.bmp",
		"engine/cubemaps/top.bmp",
		"engine/cubemaps/bottom.bmp",
		"engine/cubemaps/front.bmp",
		"engine/cubemaps/back.bmp",

	};

	cubemapTexture = LoadCubemap(list);

	InitializeCube("engine/shaders/bark.jpg");
	InitializeCube("engine/shaders/grass.jpg");
}


void Shader::Shutdown()
{
	glDeleteVertexArrays(1, &skyVAO);
	glDeleteBuffers(1, &skyVBO);
}

unsigned int Shader::CreateShader(std::string vShader, std::string fShader)
{
	std::string vContent;
	std::ifstream vStream(vShader, std::ios::in);

	if (!vStream.is_open()) {
		std::cout << "FEL - > " << vShader;
		return 0;
	}

	std::string vLine = "";
	while (!vStream.eof())
	{
		std::getline(vStream, vLine);
		vContent.append(vLine + "\n");
	}

	vStream.close();

	std::string fContent;
	std::ifstream fStream(fShader, std::ios::in);

	if (!fStream.is_open()) {
		std::cout << "FEL - > " << fShader;
		return 0;
	}

	std::string fLine = "";
	while (!fStream.eof())
	{
		std::getline(fStream, fLine);
		fContent.append(fLine + "\n");
	}

	fStream.close();

	const char* vertexCode = vContent.c_str();
	const char* fragmentCode = fContent.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

unsigned int Shader::LoadCubemap(const char* list[])
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < 6; i++)
	{
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
