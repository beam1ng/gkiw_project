#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shaderprogram.h>

class Terrain
{
private:
	void CalculateTriangles();
	void CalculateNormals();
	float trianglesVertexCount;

public:
	Terrain();
	~Terrain();

	glm::vec3 position;
	glm::vec3 rotation;
	ShaderProgram* sp;
	GLuint tex0;

	float* vertices;
	float* normals;
	int vertexCount;

	float const minTerrainHeight = 0;
	float const maxTerrainHeight = 20;

	float const terrainWidth = 1000;
	float const terrainLength = 1000;

	float const terrainResolution = 0.05f;
	float const noiseResolution = 0.005f;

	void Draw(glm::mat4 M, glm::mat4 P, glm::mat4 V);
};

