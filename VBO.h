#pragma once
#include <vector>
#include <glad/glad.h>


struct VoxelVertex {
	unsigned int x: 6;
	unsigned int y: 6;
	unsigned int z: 6;
	unsigned int voxelID: 8;
	unsigned int faceID: 3;
	unsigned int vertexID: 2;

	VoxelVertex(unsigned int x, unsigned int y, unsigned int z, unsigned int voxelID, unsigned int faceID, unsigned int vertexID) :
		x(x), y(y), z(z), voxelID(voxelID), faceID(faceID), vertexID(vertexID) {}
};


struct Vertex {
	int Position[3];
};


class VBO {
public:
	GLuint ID;

	VBO(std::vector<VoxelVertex> vertices);
	VBO(std::vector<Vertex> vertices);

	void Bind();
	void Unbind();
	void Delete();
};

