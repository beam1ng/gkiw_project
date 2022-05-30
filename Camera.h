#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 lookTarget;
	glm::vec3 upVector;

	float const followDistance = 10.0f;
	float upOffset = 1.0f;
public:
	glm::mat4 ViewMatrix;

	glm::mat4 GetViewMatrix();
	void UpdateCamera(glm::vec3 playerPosition, glm::vec3 playerDirection, glm::vec3 playerUpVector);
};

