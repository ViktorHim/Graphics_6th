#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "GLUtils.h"
#include "consts.h"
#include <sstream>
#include "lights.h"
using namespace std;

class GLModel
{	
public:
	GLModel(GLFWwindow* w) {
		mode = GL_TRIANGLES;
		glGenVertexArrays(1, &vaoID);
		window = w;
		material = nullptr;
	};

	~GLModel() {};

	size_t getVertexCount();

	void setVmatrix(glm::mat4 Vmatrix);
	void setPmatrix(glm::mat4 Pmatrix);
	void setMmatrix(glm::mat4 Mmatrix);
	void setMaterial(Material * material);
	void setMode(GLuint mode);
	void setShaderProgram(GLuint shaderProgramID);

	void render();
	void renderWithLights(LightsInfo* lights, glm::vec3 cameraPosition);
	void loadCoords(glm::vec3* verteces, size_t count);
	void loadNormals(glm::vec3* normals, size_t count);

	void loadColors(glm::vec3* colors, size_t count);
	void loadIndexes(GLuint * indices, size_t count);

private:

	GLuint vaoID = -1;
	size_t vertexCount = 0;
	size_t indexCount = 0;

	GLuint shaderProgramID = -1;
	glm::mat4 Pmatrix = glm::mat4(1.0f);
	glm::mat4 Vmatrix = glm::mat4(1.0f);
	glm::mat4 Mmatrix = glm::mat4(1.0f);

	GLuint mode;
	GLFWwindow* window;

	void applyMaterial();
	void applyMatrix();
	void applyLights(LightsInfo* lights, glm::vec3 cameraPosition);

	Material * material;
};

