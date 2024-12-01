#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


class Mesh{
	public:
		int numVertices;

		VAO VAO;

		Mesh();
		Mesh(std::vector<VoxelVertex> vertices, std::vector<GLuint> indices);
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
		void Draw(Shader& shader);
		void Delete();
};

