#include "App.h"


void APIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user) {
	std::cerr << message << std::endl;
}


App::App(const char* name, int width, int height) :
	name(name),
	width(width),
	height(height),
	player(glm::vec3(0, 33, 0), 90.0f, 90.0f, width, height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glfwSwapInterval(1);

	stbi_set_flip_vertically_on_load(1);

	glViewport(0, 0, width, height); 

	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetCursorPos(window, (float)width / 2, (float)height / 2);
}


void App::Run() {

	std::string title;

	Shader skyShader("sky");
	Shader shader("default");

	Skybox skybox;

	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			generateChunk(glm::vec3(x, 0, z));
		}
	}

	TextureArray blockTextureArray("Blocks/block_texture_array.png", GL_TEXTURE0);

	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "textureArray"), 0);


	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		player.handleInputs(window);

		glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.camera.updateMatrices();

		blockTextureArray.Bind();

		renderChunks(shader, player.camera);

		skybox.Draw(skyShader, player.camera);

		glfwSwapBuffers(window);

		prevTime = currentTime;
		currentTime = glfwGetTime();;
		deltaTime = currentTime - prevTime;
		fps = fps * 0.9 + 0.1 / deltaTime;

		title = name + " | " + std::to_string(int(fps)) + " FPS | " + std::to_string(int(deltaTime * 1000)) + " ms";
		glfwSetWindowTitle(window, title.c_str());
		glGetError();
	}

	shader.Delete();
	skyShader.Delete();
	skybox.mesh.Delete();
	glDeleteTextures(1, &blockTextureArray.ID);
	glfwDestroyWindow(window);
	glfwTerminate();
}


void App::generateChunk(glm::vec3 pos) {
	int index = (int)chunks.size();
	chunks.push_back(std::make_unique<Chunk>(&chunks, pos));
	chunkIndices[vec3Hash(pos)] = index;
}


void App::renderChunks(Shader shader, Camera camera) {
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			glm::vec3 pos = glm::vec3(x, 0, z);
			int index = chunkIndices[vec3Hash(pos)];
			chunks[index]->Draw(shader, player.camera);
		}
	}
}


int App::vec3Hash(glm::vec3 vec) {
	return ((int)vec.x << 20) | ((int)vec.y << 10) | ((int)vec.z);
}

