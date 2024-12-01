#include "TextureArray.h"


TextureArray::TextureArray(std::string path, GLuint glTexture) {

	TextureArray::glTexture = glTexture;

	std::string textureFolder = "Resources/Textures/";
	unsigned char* bytes = stbi_load((textureFolder + path).c_str(), &width, &height, &numCC, 0);

	glGenTextures(1, &ID);
	Bind(glTexture);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, 10, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}


void TextureArray::Activate() {
	glActiveTexture(glTexture);
}


void TextureArray::Activate(GLuint glTexture) {
	glActiveTexture(glTexture);
}


void TextureArray::Bind() {
	Activate();
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}


void TextureArray::Bind(GLuint glTexture) {
	Activate(glTexture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}


void TextureArray::Unbind() {
	Activate();
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

