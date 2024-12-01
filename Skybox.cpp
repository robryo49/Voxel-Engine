#include "Skybox.h"


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


Skybox::Skybox() :
	mesh(
		std::vector<Vertex> {
			Vertex{ -1,		-1,		-1	 },
			Vertex{ 1,		-1,		-1	 },
			Vertex{ 1,		-1,		1	 },
			Vertex{ -1,		-1,		1	 },

			Vertex{ -1,		1,		-1	 },
			Vertex{ 1,		1,		-1	 },
			Vertex{ 1,		1,		1	 },
			Vertex{ -1,		1,		1	 },
	},

	std::vector<GLuint>{
		1, 0, 2, 3, 0xFFFF,
		5, 6, 4, 7, 0xFFFF,
		1, 5, 0, 4, 0xFFFF,
		2, 3, 6, 7, 0xFFFF,
		4, 7, 0, 3, 0xFFFF,
		5, 1, 6, 2, 0xFFFF,
	}
	) {

}


void Skybox::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mCamera"), 1, GL_FALSE, glm::value_ptr(camera.mSkybox));
	mesh.Draw(shader);
}

