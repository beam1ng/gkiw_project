#define GLM_FORCE_SWIZZLE

#include "Player.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "Utility.h"
#include <myTeapot.h>


Player::Player() {
	Player::position = glm::vec3(0, 10, 0);
	Player::direction = glm::vec3(0, 0, 1);
	Player::upVector = glm::vec3(0, 1, 0);
	Player::sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	Player::tex0 = Utility::readTexture("metal.png");
	Player::tex1 = Utility::readTexture("sky.png");

	Player::vertices = myTeapotVertices;
	Player::normals = myTeapotVertexNormals;
	Player::texCoords = myTeapotTexCoords;
	Player::colors = myTeapotColors;
	Player::vertexCount = myTeapotVertexCount;
}

Player::~Player() {
	delete sp;
}

void Player::Draw(glm::mat4 M, glm::mat4 P, glm::mat4 V)
{
	position = position + direction * 0.1f + glm::vec3(0,-1,0) * 0.01f;

	translation = glm::translate(M, position);

	Player::Model = translation * glm::mat4_cast(Player::orientation)* M;

	sp->use();//Aktywacja programu cieniuj?cego
	//Przeslij parametry programu cieniuj?cego do karty graficznej
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Player::Model));

	glEnableVertexAttribArray(sp->a("vertex"));  //W??cz przesy?anie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska? tablic? z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //W??cz przesy?anie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wska? tablic? z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //W??cz przesy?anie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska? tablic? z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //W??cz przesy?anie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska? tablic? z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wy??cz przesy?anie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wy??cz przesy?anie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wy??cz przesy?anie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy??cz przesy?anie danych do atrybutu texCoord0
}
//todo: do
void Player::UpdateRotation(glm::vec3 input, float deltaTime)
{
	if (input == glm::vec3(0)) {
		return;
	}

	float currentSpin = (abs(input.x) * yawSpeed + abs(input.y) * pitchSpeed + abs(input.z) * rollSpeed) * deltaTime;

	glm::vec3 rotationAxis = Player::orientation * glm::normalize(glm::vec3(input.y, -input.x, input.z));

	glm::quat rotation;

	rotation.x = rotationAxis.x * sin(glm::radians(currentSpin / 2));
	rotation.y = rotationAxis.y * sin(glm::radians(currentSpin / 2));
	rotation.z = rotationAxis.z * sin(glm::radians(currentSpin / 2));
	rotation.w = cos(glm::radians(currentSpin / 2));

	Player::orientation = rotation * Player::orientation;

	Player::direction = Player::orientation * glm::vec3(0, 0, 1);
	Player::upVector = Player::orientation * glm::vec3(0, 1, 0);
}

void Player::UpdatePosition(float inputSpeed, float deltaTime) {
	
	Player::speed = glm::clamp(Player::speed + inputSpeed * deltaTime * speedChangeAmplifier, Player::minSetSpeed, Player::maxSetSpeed);

	//gravity at 0 sinusoidal interpolation to minFlightSpeed
	float fallFromSpeed =  0.5f + glm::clamp(-1*(float)sin(-3.14f/2 + 3.14f*glm::clamp(Player::speed/Player::minFlightSpeed,0.0f,1.0f)) / 2,-0.5f,0.5f);

	//gravity at horizontal
	float fallFromOrientation = glm::clamp(1-(float)glm::dot(glm::normalize(Player::upVector),glm::vec3(0,1,0)),0.0f,1.0f);

	float fallTotal = Player::gravity * glm::clamp(fallFromSpeed + fallFromOrientation * 0.5f, 0.0f, 1.0f) * deltaTime;


	float forwardDistance = Player::speed * deltaTime;

	Player::position = Player::position + glm::vec3(0, -1, 0) * fallTotal + direction * forwardDistance;
}

void Player::Update(glm::vec4 input, float deltaTime) {
	UpdateRotation(input.xyz, deltaTime);
	UpdatePosition(input.w, deltaTime);
}