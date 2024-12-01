#include "Player.h"


Player::Player(glm::vec3 position, float rotation, float FOV, int width, int height) :
	camera(FOV, width, height, 0.01f, 1000.0f, position, 0.0f, 0.0f),
	Position(position),
	Rotation(rotation),
	Forward(glm::vec3(glm::cos(glm::radians(rotation)), 0, glm::sin(glm::radians(rotation)))),
	Right(glm::normalize(glm::cross(Forward, Up))),
	prevMousePos(glm::vec2((width / 2), (height / 2))) {
}


void Player::handleInputs(GLFWwindow* window) {
	speed = glfwGetKey(window, GLFW_KEY_R) ? fastFlySPeed: flySpeed;

	if (glfwGetKey(window, GLFW_KEY_W))				Position +=	speed * Forward;
	if (glfwGetKey(window, GLFW_KEY_A))				Position +=	speed * -Right;
	if (glfwGetKey(window, GLFW_KEY_S))				Position +=	speed * -Forward;
	if (glfwGetKey(window, GLFW_KEY_D))				Position +=	speed * Right;
	if (glfwGetKey(window, GLFW_KEY_SPACE))			Position +=	speed * Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))	Position +=	speed * -Up;

	if (glfwGetKey(window, GLFW_KEY_F3)) { keyPressDurations[GLFW_KEY_F3]++; } else keyPressDurations[GLFW_KEY_F3] = 0;

	if (glfwGetKey(window, GLFW_KEY_Z)) {
		keyPressDurations[GLFW_KEY_Z]++;

		if (keyPressDurations[GLFW_KEY_Z] == 1 && keyPressDurations[GLFW_KEY_F3]) {
			GLint polygonMode[2];
			glGetIntegerv(GL_POLYGON_MODE, polygonMode);

			if (polygonMode[0] == GL_FILL) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); std::cout << "lining"; 
			} else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); std::cout << "filling"; }
			
		}

	} else keyPressDurations[GLFW_KEY_Z] = 0;


	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	float xRotation = getMouseRotation(mouseX - prevMousePos.x);
	float yRotation = getMouseRotation(mouseY - prevMousePos.y);
	Rotation += xRotation;
	Rotation = Rotation - int(Rotation / 360.0) * 360;
	camera.Yaw = Rotation;
	camera.Pitch = glm::max(-89.0f, glm::min(camera.Pitch - yRotation, 89.0f));

	glfwSetCursorPos(window, (float)camera.Width / 2, (float)camera.Height / 2);

	updateVectors();

}


void Player::updateVectors() {
	Forward.x = glm::cos(glm::radians(Rotation));
	Forward.z = glm::sin(glm::radians(Rotation));
	Forward = glm::normalize(Forward);

	Right = glm::normalize(glm::cross(Forward, Up));

	camera.Forward.x = glm::cos(glm::radians(camera.Yaw)) * glm::cos(glm::radians(camera.Pitch));
	camera.Forward.y = glm::sin(glm::radians(camera.Pitch));
	camera.Forward.z = glm::sin(glm::radians(camera.Yaw)) * glm::cos(glm::radians(camera.Pitch));

	camera.Forward = glm::normalize(camera.Forward);
	camera.Right = glm::normalize(glm::cross(camera.Forward, Up));
	camera.Up = glm::normalize(glm::cross(camera.Forward, camera.Right));

	camera.Position = Position;
}


float Player::getMouseRotation(double movement) {
	int direction = 1 - 2 * signbit(movement);
	float power = pow(abs(movement) * Reactiveness, Steepness);
	return Sensitivity * (power / (1 + power)) * direction;
}

