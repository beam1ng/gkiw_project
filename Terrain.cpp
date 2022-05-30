#include "Terrain.h"
#include <SimplexNoise.h>
#include "Utility.h"

void Terrain::CalculateTriangles() {
	int const terrainWidth = Terrain::terrainWidth;
	int const terrainLength = Terrain::terrainLength;

	int terrainWidthHeights = (int)(terrainWidth * terrainResolution);
	int terrainLengthHeights = (int)(terrainLength * terrainResolution);

	int heightsCount = terrainLengthHeights * terrainWidthHeights;
	Terrain::trianglesVertexCount = (terrainLengthHeights - 1) * (terrainWidthHeights - 1) * 6;

	float* terrainHeights = new float[heightsCount];
	float* terrainTriangles = new float[4 * Terrain::trianglesVertexCount];//each vertex is 4D

	for (int i = 0; i < terrainWidthHeights; i++) {
		for (int j = 0; j < terrainLengthHeights; j++) {
			terrainHeights[i * terrainWidthHeights + j] = glm::mix(minTerrainHeight,maxTerrainHeight,SimplexNoise::noise((float)i * noiseResolution / terrainResolution, (float)j * noiseResolution / terrainResolution));
		}
	}
	for (int i = 0; i < terrainWidthHeights - 1; i++) {
		for (int j = 0; j < terrainLengthHeights - 1; j++) {
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j)] = (i) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 1] = terrainHeights[i * terrainWidthHeights + j];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 2] = (j) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 3] = 1.0f;

			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 4] = (i + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 5] = terrainHeights[(i + 1) * terrainWidthHeights + j];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 6] = (j) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 7] = 1.0f;

			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 8] = (i) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 9] = terrainHeights[i * terrainWidthHeights + j + 1];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 10] = (j + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 11] = 1.0f;

			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 12] = (i + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 13] = terrainHeights[(i + 1) * terrainWidthHeights + j];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 14] = (j) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 15] = 1.0f;

			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 16] = (i + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 17] = terrainHeights[(i + 1) * terrainWidthHeights + j + 1];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 18] = (j + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 19] = 1.0f;

			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 20] = (i) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 21] = terrainHeights[i * terrainWidthHeights + j + 1];
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 22] = (j + 1) / terrainResolution;
			terrainTriangles[6 * 4 * ((terrainWidthHeights - 1) * i + j) + 23] = 1.0f;
		}
	}

	Terrain::vertexCount = trianglesVertexCount;
	Terrain::vertices = terrainTriangles;
	delete[] terrainHeights;
	return;
}

void Terrain::CalculateNormals() {

	float* terrainNormals = new float[4 * trianglesVertexCount];

	for (int i = 0; i < 4 * trianglesVertexCount; i += 12) {
		glm::vec3 vec1 = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		glm::vec3 vec2 = glm::vec3(vertices[i + 4], vertices[i + 5], vertices[i + 6]);
		glm::vec3 vec3 = glm::vec3(vertices[i + 8], vertices[i + 9], vertices[i + 10]);

		glm::vec3 normal = glm::cross(vec3 - vec1, vec2 - vec1);

		terrainNormals[i] = normal.x;
		terrainNormals[i + 1] = normal.y;
		terrainNormals[i + 2] = normal.z;
		terrainNormals[i + 3] = 1.0f;

		terrainNormals[i + 4] = normal.x;
		terrainNormals[i + 5] = normal.y;
		terrainNormals[i + 6] = normal.z;
		terrainNormals[i + 7] = 1.0f;

		terrainNormals[i + 8] = normal.x;
		terrainNormals[i + 9] = normal.y;
		terrainNormals[i + 10] = normal.z;
		terrainNormals[i + 11] = 1.0f;
	}
	Terrain::normals = terrainNormals;
	return;
}

Terrain::Terrain()
{
	Terrain::position = glm::vec3(0, -3, 0);
	Terrain::rotation = glm::vec3(0, 0, 0);
	Terrain::sp = new ShaderProgram("v_terrain.glsl", NULL, "f_terrain.glsl");
	Terrain::tex0 = Utility::readTexture("grass.png");
	CalculateTriangles();
	CalculateNormals();
}

Terrain::~Terrain()
{
	delete sp;
	delete[] Terrain::vertices; //I delete only verticies because colors and normals reference the same dynamic array
	delete[] Terrain::normals;
}

void Terrain::Draw(glm::mat4 M, glm::mat4 P, glm::mat4 V)
{
	glm::vec3 offset = glm::vec3(-terrainWidth / 2, 0, -terrainLength / 2);
	glm::vec3 finalPosition = offset + Terrain::position;
	glm::mat4 Model = glm::translate(M, finalPosition);

	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Model));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, Terrain::vertices);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, Terrain::normals);

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

	glDrawArrays(GL_TRIANGLES, 0, Terrain::vertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normals"));
}
