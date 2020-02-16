#include "Cube.h"

void Cube::Instantiate(Math::Vector3 pos, Math::Vector3 scale, unsigned int texture) {
	glUseProgram(cube);
	void* mPtr = &model;
	const float* modelPtr = (float*)mPtr;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(cube, "txt"), 0);

	GLint modelLoc = glGetUniformLocation(cube, "model");
	GLint viewLoc = glGetUniformLocation(cube, "view");
	GLint projLoc = glGetUniformLocation(cube, "projection");

	glUniformMatrix4fv(viewLoc, 1, 0, viewPtr);
	glUniformMatrix4fv(projLoc, 1, 0, projPtr);

	glBindVertexArray(VAO);

	model = Math::Translate(pos);
	model.m[0][0] = scale.x; // scaling, tempfix
	model.m[1][1] = scale.y;
	model.m[2][2] = scale.z;
	model.m[3][3] = 1;

	glUniformMatrix4fv(modelLoc, 1, 0, modelPtr);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::Render(Player player) {
	projection = Math::Perspective(60.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);
	view = player.GetView();

	void* vPtr = &view;
	viewPtr = (float*)vPtr;

	void* pPtr = &projection;
	projPtr = (float*)pPtr;
}

unsigned int Cube::Initialize(const char* path) {
	unsigned int texture;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, 3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

void Cube::Startup() {
	cube = CreateShader("engine/resources/shaders/core.vs", "engine/resources/shaders/core.frag");
}
