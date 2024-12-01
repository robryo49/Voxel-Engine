#include "Chunk.h"


// **  y
//     4------------5
//    /|           /|
//   / |          / |
//  /  |         /  |
// 7------------6   |
// |   |        |   |
// |   0--------|---1 x
// |  /         |  /
// | /          | /
// |/           |/
// 3------------2
//z
// 
//    1 2
//    |/
// 4--+--5
//   /|
//  3 0



static void addVoxelData(std::vector<VoxelVertex>* vertices) {

}



Chunk::Chunk(std::vector<std::unique_ptr<Chunk>>* chunks, glm::vec3 position) :
	Position(position),
	mPosition(glm::translate(dimensions * position)) {

	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int z = 0; z < dimensions.z; z++) {
				voxels[x][y][z] = (int)(- x + y - z < 0);
			}
		}
	}

	generateMesh();
}


void Chunk::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mCamera"), 1, GL_FALSE, glm::value_ptr(camera.mWorld * mPosition));
	mesh.Draw(shader);
}


void Chunk::generateMesh() {

	std::vector<VoxelVertex> vertices = {
	};


	std::vector<GLuint> indices = {
	};

	unsigned int i = 0;
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int z = 0; z < dimensions.z; z++) {
				uint8_t voxel = voxels[x][y][z];

				//bool down =		(y - 1 >= 0) ?				!(voxels[x][y - 1][z]) : true;
				//bool up =		(y + 1 < dimensions.y) ?	!(voxels[x][y + 1][z]) : true;
				//bool front =	(z - 1 >= 0) ?				!(voxels[x][y][z - 1]) : true;
				//bool back =		(z + 1 < dimensions.z) ?	!(voxels[x][y][z + 1]) : true;
				//bool left =		(x - 1 >= 0) ?				!(voxels[x - 1][y][z]) : true;
				//bool right =	(x + 1 < dimensions.x) ?	!(voxels[x + 1][y][z]) : true;
				bool down =		voxelEmpty(glm::vec3(x, y - 1, z), 1);
				bool up =		voxelEmpty(glm::vec3(x, y + 1, z), 1);
				bool front =	voxelEmpty(glm::vec3(x, y, z - 1), 1);
				bool back =		voxelEmpty(glm::vec3(x, y, z + 1), 1);
				bool left =		voxelEmpty(glm::vec3(x - 1, y, z), 1);
				bool right =	voxelEmpty(glm::vec3(x + 1, y, z), 1);

				if (voxel) {
					if (down) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 0, y + 0, z + 0,		voxel,		0,		0),
								VoxelVertex(x + 1, y + 0, z + 0,		voxel,		0,		1),
								VoxelVertex(x + 1, y + 0, z + 1,		voxel,		0,		3),
								VoxelVertex(x + 0, y + 0, z + 1,		voxel,		0,		2)
						});
						indices.insert(indices.end(), { 1 + i, 2 + i, 0 + i, 3 + i, 0xFFFF});
						i = i + 4;
					}

					if (up) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 0, y + 1, z + 0,		voxel,		1,		3),
								VoxelVertex(x + 1, y + 1, z + 0,		voxel,		1,		2),
								VoxelVertex(x + 1, y + 1, z + 1,		voxel,		1,		0),
								VoxelVertex(x + 0, y + 1, z + 1,		voxel,		1,		1)
							});
						indices.insert(indices.end(), { 1 + i, 0 + i, 2 + i, 3 + i, 0xFFFF });
						i = i + 4;
					}

					if (front) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 0, y + 0, z + 0,		voxel,		2,		1),
								VoxelVertex(x + 1, y + 0, z + 0,		voxel,		2,		0),
								VoxelVertex(x + 1, y + 1, z + 0,		voxel,		2,		2),
								VoxelVertex(x + 0, y + 1, z + 0,		voxel,		2,		3)
							});
						indices.insert(indices.end(), { 1 + i, 0 + i, 2 + i, 3 + i, 0xFFFF });
						i = i + 4;
					}

					if (back) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 0, y + 0, z + 1,		voxel,		3,		0),
								VoxelVertex(x + 1, y + 0, z + 1,		voxel,		3,		1),
								VoxelVertex(x + 1, y + 1, z + 1,		voxel,		3,		3),
								VoxelVertex(x + 0, y + 1, z + 1,		voxel,		3,		2)
							});
						indices.insert(indices.end(), { 1 + i, 2 + i, 0 + i, 3 + i, 0xFFFF });
						i = i + 4;
					}

					if (left) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 0, y + 0, z + 0,		voxel,		4,		0),
								VoxelVertex(x + 0, y + 1, z + 0,		voxel,		4,		2),
								VoxelVertex(x + 0, y + 1, z + 1,		voxel,		4,		3),
								VoxelVertex(x + 0, y + 0, z + 1,		voxel,		4,		1)
							});
						indices.insert(indices.end(), { 1 + i, 0 + i, 2 + i, 3 + i, 0xFFFF });
						i = i + 4;
					}

					if (right) {
						vertices.insert(vertices.end(), {
								VoxelVertex(x + 1, y + 0, z + 0,		voxel,		5,		1),
								VoxelVertex(x + 1, y + 1, z + 0,		voxel,		5,		3),
								VoxelVertex(x + 1, y + 1, z + 1,		voxel,		5,		2),
								VoxelVertex(x + 1, y + 0, z + 1,		voxel,		5,		0)
							});
						indices.insert(indices.end(), { 1 + i, 2 + i, 0 + i, 3 + i, 0xFFFF });
						i = i + 4;
					}
				}
			}
		}
	}

	mesh = Mesh(vertices, indices);
}


bool Chunk::voxelEmpty(glm::vec3 pos, int LODLevel) {
	if (0 <= pos.x && pos.x < dimensions.x && 0 <= pos.y && pos.y < dimensions.y && 0 <= pos.z && pos.z < dimensions.z) {
		return !(voxels[(int)pos.x][(int)pos.y][(int)pos.z]);
	}
	else {
		glm::vec3 chunkPos = pos / dimensions.x;
		return true;
	}
}

