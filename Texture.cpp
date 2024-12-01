#include "Texture.h"


Texture::Texture(std::string path, GLuint glTexture) {

	Texture::glTexture = glTexture;

	std::string textureFolder = "Resources/Textures/";
	unsigned char* bytes = stbi_load((textureFolder + path).c_str(), &width, &height, &numCC, 0);

	glGenTextures(1, &ID);
	Bind(glTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Activate() {
	glActiveTexture(glTexture);
}


void Texture::Activate(GLuint glTexture) {
	glActiveTexture(glTexture);
}


void Texture::Bind() {
	Activate();
	glBindTexture(GL_TEXTURE_2D, ID);
}


void Texture::Bind(GLuint glTexture) {
	Activate(glTexture);
	glBindTexture(GL_TEXTURE_2D, ID);
}


void Texture::Unbind() {
	Activate();
	glBindTexture(GL_TEXTURE_2D, 0);
}

