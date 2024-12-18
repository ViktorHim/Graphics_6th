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
#include <algorithm>

using namespace std;

class GLUtils
{
public:
	/// <summary>
	/// Loading a shader from a file
	/// </summary>
	/// <param name="filename">Path to file.</param>
	/// <returns>String with shader code.</returns>
	static string LoadShader(const char* filename);
	static GLuint CreateShaderProgram(const char* vertexFilename, const char* fragmentFilename, string attr);
	static vector<glm::vec3> Normalize(vector<glm::vec3> vertexes);
	static vector<glm::vec3> GeneratePolygonNormalize(int n, int scaleX, int scaleY, float offsetX = 0, float offsetY = 0, float rotation = 0);
	static vector<glm::vec3> GeneratePolygon(int n, int scaleX, int scaleY, float offsetX = 0, float offsetY = 0, float rotation = 0);
	static vector<glm::vec3> TranslateXY(vector<glm::vec3> vertexes, float x, float y);
	static bool loadOBJ(
		const char* path, //���� � �����
		vector<glm::vec3>& outVertices, //�������� ������ ���������
		vector<glm::vec2>& outTextures, //�������� ������ ���������� ���������
		vector<glm::vec3>& outNormals //�������� ������ ��������
	);
	static void genSphere(
		std::vector<GLuint>& outIndexes, //�������� ������ ��������
		std::vector < glm::vec3 >& outVertices, //�������� ������ ���������
		std::vector < glm::vec2 >& outTextures, //�������� ������ ���������� ���������
		std::vector < glm::vec3 >& outNormals, //�������� ������ �������� ��������
		float radius, //������ �����
		int sectorCount, //����� ����������
		int stackCount //����� ����������
	);
	static void genCylinder(
		std::vector<GLuint>& outIndexes, //�������� ������ ��������
		std::vector < glm::vec3 >& outVertices, //�������� ������ ���������
		std::vector < glm::vec2 >& outTextures, //�������� ������ ���������� ���������
		std::vector < glm::vec3 >& outNormals, //�������� ������ �������� ��������
		float baseRadius, //������ ���������
		float topRadius, //������ �������
		float height, //������
		int sectorCount, //����� ������
		int stackCount //����� ������
	);
	void genTorus(
		std::vector<GLuint>& outIndexes, //�������� ������ ��������
		std::vector < glm::vec3 >& outVertices, //�������� ������ ���������
		std::vector < glm::vec2 >& outTextures, //�������� ������ ���������� ���������
		std::vector < glm::vec3 >& outNormals, //�������� ������ �������� ��������
		float outerRadius, //������� ������
		float tubeRadius, //������ ������ ����
		int sectorCount, //����� ������
		int stackCount //����� ������
	);
	/// <summary>
	/// ������� ������������� ����� � �������� ����.
	/// </summary>
	/// <param name="w">������ ����.</param>
	/// <param name="h">������ ����.</param>
	/// <param name="Fullscreen">����� ������� ������. </param>
	/// <param name="title">Window title</param>
	/// <returns>��������� �� ��������� ����.</returns>
	static GLFWwindow* Init(int w = 640, int h = 480, bool Fullscreen = false, string title = "test");
	/// <summary>
	/// Function for correct program termination.
	/// </summary>
	static void Clear();
};

