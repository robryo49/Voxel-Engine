#include "Mesh.h"


Mesh::Mesh() {
	numVertices = 0;
}


Mesh::Mesh(std::vector<VoxelVertex> vertices, std::vector<GLuint> indices) {

	numVertices = (int)indices.size();

	VAO.Bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 1, GL_UNSIGNED_INT, sizeof(VoxelVertex), (void*)0);
	VAO.Unbind();

	VBO.Unbind();
	EBO.Unbind();

	//VBO.Delete();
	//EBO.Delete();
}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) {

	numVertices = (int)indices.size();

	VAO.Bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_INT, 3 * sizeof(int), (void*)(0));
	VAO.Unbind();

	VBO.Unbind();
	EBO.Unbind();

	// VBO.Delete();
	// EBO.Delete();
}


void Mesh::Draw(Shader& shader) {
	shader.Activate();
	VAO.Bind();
	glDrawElements(GL_TRIANGLE_STRIP, numVertices, GL_UNSIGNED_INT, 0);
}


void Mesh::Delete() {
	VAO.Delete();
}
