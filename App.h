#pragma once
#include <glad/glad.h>
#include "Player.h"
#include "Skybox.h"
#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureArray.h"


class App {
	public:
		GLFWwindow* window;
		bool wireframeView = false;
		bool vSync = true;

		Player player;

		std::vector<std::unique_ptr<Chunk>> chunks;
		std::unordered_map<int, int> chunkIndices;

		std::string name;
		int width;
		int height;
		GLfloat bgColor[4] = { 0.15f, 0.25f, 0.45f, 1.0f };

		double currentTime = 0.0f;
		double prevTime = 0.0f;
		double deltaTime = 0.0f;
		double fps = 0.0f;

		App(const char* name, int width, int height);
		void Run();

		void generateChunk(glm::vec3 pos);
		void renderChunks(Shader shader, Camera camera);
		int vec3Hash(glm::vec3 vec);
};

