#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Camera.h"


class Skybox {
public:

	Mesh mesh;

	Skybox();
	void Draw(Shader& shader, Camera& camera);
};

