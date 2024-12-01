#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>


class Texture {
	public:
		GLuint ID;
		GLuint glTexture;

		int width, height, numCC;

		Texture(std::string path, GLuint glTexture);
		void Unbind();
		void Bind();
		void Bind(GLuint glTexture);
		void Activate();
		void Activate(GLuint glTexture);
};

