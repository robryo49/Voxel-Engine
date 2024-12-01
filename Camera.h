#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Camera {
	public:
		float FOV;
		float vFOV;
		int Width;
		int Height;
		float aspectRatio;
		float Near;
		float Far;

		glm::vec3 Position;
		float Yaw;		// Left-Right
		float Pitch;	// Up-Down

		glm::vec3 Up = glm::vec3(0, 1, 0);
		glm::vec3 Right = glm::vec3(1, 0, 0);
		glm::vec3 Forward = glm::vec3(0, 0, 1);

		glm::mat4 mWorld = glm::mat4(1.0f);
		glm::mat4 mSkybox = glm::mat4(1.0f);

		Camera(float FOV, int width, int height, float near, float far, glm::vec3 position, float yaw, float pitch);
		void updateMatrices();
};

