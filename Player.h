#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <unordered_map>
#include <iostream>
#include "Camera.h"


class Player{
	public:
		Camera camera;

		glm::vec3 Position;
		float Rotation;

		float speed = 0.1f;
		float walkingSpeed = 0.07f;
		float flySpeed = 0.5f;
		float fastFlySPeed = 2.0f;

		float Sensitivity = 15.0f;
		float Reactiveness = 0.01f;
		float Steepness = 1.0f;

		glm::vec3 Up = glm::normalize(glm::vec3(0, 1, 0));
		glm::vec3 Forward;
		glm::vec3 Right;

		glm::vec2 prevMousePos;

		std::unordered_map<int, int> keyPressDurations = {
			{GLFW_KEY_F3, 0},
			{GLFW_KEY_W, 0},
		};

		Player(glm::vec3 position, float rotation, float FOV, int width, int height);

		void handleInputs(GLFWwindow* window);
		void updateVectors();
		float getMouseRotation(double movement);
};

