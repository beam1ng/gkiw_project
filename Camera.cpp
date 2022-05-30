#include "Camera.h"

glm::mat4 Camera::GetViewMatrix()
{
	return ViewMatrix;
}

void Camera::UpdateCamera(glm::vec3 playerPosition, glm::vec3 playerDirection, glm::vec3 playerUpVector)
{
	Camera::upVector = playerUpVector;
	Camera::position = playerPosition - glm::normalize(playerDirection) * followDistance + playerUpVector * upOffset;
	Camera::lookTarget = playerPosition;

	ViewMatrix = glm::lookAt(Camera::position, Camera::lookTarget, Camera::upVector);
	//ViewMatrix = glm::lookAt(glm::vec3(0, -1, 5), glm::vec3(0), glm::vec3(0, 1, 0));
}
