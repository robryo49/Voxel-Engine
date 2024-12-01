#include "Camera.h"



Camera::Camera(float FOV, int width, int height, float near, float far, glm::vec3 position, float yaw, float pitch) :
	Width(width),
	Height(height),
	aspectRatio((float)width / height),

	Near(near),
	Far(far),

	FOV(glm::radians(FOV)),
	vFOV(2.0f * atan(tan(glm::radians(FOV) / 2.0f) / ((float)width / height))),

	Position(position),
	Yaw(yaw),
	Pitch(pitch)
	{

}


void Camera::updateMatrices() {
	glm::mat4 mView = glm::lookAt(Position, Position + Forward, -Up);
	glm::mat4 mProj = glm::perspective(vFOV, (float)Width / Height, Near, Far);
	mWorld = mProj * mView;
	mSkybox = mProj * glm::mat4(glm::mat3(mView));
}

