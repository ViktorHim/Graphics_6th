#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MAX_NUM_LIGHTS 10

struct DirLight
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct PointLight
{
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SpotLight
{
	glm::vec3 position;
	glm::vec3 direction;
	// Параметры угла
	float cutOff;
	float outerCutOff;
	// Параметры затухания
	float constant;
	float linear;
	float quadratic;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct LightsInfo
{
	DirLight dirLight;
	PointLight pointLights[MAX_NUM_LIGHTS];
	SpotLight spotLights[MAX_NUM_LIGHTS];
	int numPLights;
	int numSLights;
};

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};
