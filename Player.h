#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shaderprogram.h>

class Player
{
private:
	ShaderProgram* sp;
	GLuint tex0;
	GLuint tex1;
	glm::mat4 Model = glm::mat4(1);
	glm::quat orientation = glm::quat(1, 0, 0, 0);
	glm::mat4 translation = glm::mat4(1);

	float speed = 10.0f;
	float yawSpeed = 2.0f;
	float pitchSpeed = 14.0f;
	float rollSpeed = 24.0f;
	float speedChangeAmplifier = 10.0f;

	float minSetSpeed = 1.0f;
	float maxSetSpeed = 50.0f;

	float minFlightSpeed = 8.0f;
	float gravity = 10.0f;

	float* vertices;
	float* normals;
	float* texCoords;
	float* colors;
	int vertexCount;

	void UpdateRotation(glm::vec3 input, float deltaTime);
	void UpdatePosition(float inputSpeed, float deltaTime);
public:
	Player();
	~Player();

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 upVector;


	void Update(glm::vec4 input, float deltaTime);
	void Draw(glm::mat4 M, glm::mat4 P, glm::mat4 V);
};

