#pragma once
#include "Mesh.h"
#include "Camera.h"


class Chunk {
public:
	glm::vec3 dimensions = glm::vec3(32);

	glm::vec3 Position;
	glm::mat4 mPosition;

	char voxels[32][32][32]{};

	Mesh mesh;

	Chunk(std::vector<std::unique_ptr<Chunk>>* chunks, glm::vec3 position);
	void Draw(Shader& shader, Camera& camera);
	void generateMesh();
	bool voxelEmpty(glm::vec3 pos, int LODLevel);
};
