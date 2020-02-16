#include "Skybox.h"

void Skybox::Shutdown() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Skybox::Render(Player player) {
	view = player.GetView();
	projection = Math::Perspective(60.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);
	Math::Matrix4 model;

	void* mPtr = &model;
	const float* modelPtr = (float*)mPtr;

	void* vPtr = &view;
	viewPtr = (float*)vPtr;

	void* pPtr = &projection;
	projPtr = (float*)pPtr;

	glDepthFunc(GL_LEQUAL);
	glUseProgram(sky);

	view = Math::To3x3((player.GetView()));
	glUniformMatrix4fv(glGetUniformLocation(sky, "view"), 1, 0, viewPtr);
	glUniformMatrix4fv(glGetUniformLocation(sky, "projection"), 1, 0, projPtr);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void Skybox::Startup() {
	sky = CreateShader("engine/resources/shaders/skybox.vs", "engine/resources/shaders/skybox.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	const char* list[6] = {
		"engine/resources/cubemaps/right.bmp",
		"engine/resources/cubemaps/left.bmp",
		"engine/resources/cubemaps/top.bmp",
		"engine/resources/cubemaps/bottom.bmp",
		"engine/resources/cubemaps/front.bmp",
		"engine/resources/cubemaps/back.bmp",
	};

	cubemapTexture = LoadCubemap(list);
}