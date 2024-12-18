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
		const char* path, //Путь к файлу
		vector<glm::vec3>& outVertices, //Выходной массив координат
		vector<glm::vec2>& outTextures, //Выходной массив текстурных координат
		vector<glm::vec3>& outNormals //Выходной массив нормалей
	);
	static void genSphere(
		std::vector<GLuint>& outIndexes, //Выходной массив индексов
		std::vector < glm::vec3 >& outVertices, //Выходной массив координат
		std::vector < glm::vec2 >& outTextures, //Выходной массив текстурных координат
		std::vector < glm::vec3 >& outNormals, //Выходной массив векторов нормалей
		float radius, //Радиус сферы
		int sectorCount, //Число меридианов
		int stackCount //Число параллелей
	);
	static void genCylinder(
		std::vector<GLuint>& outIndexes, //Выходной массив индексов
		std::vector < glm::vec3 >& outVertices, //Выходной массив координат
		std::vector < glm::vec2 >& outTextures, //Выходной массив текстурных координат
		std::vector < glm::vec3 >& outNormals, //Выходной массив векторов нормалей
		float baseRadius, //Радиус основания
		float topRadius, //Радиус вершины
		float height, //Высота
		int sectorCount, //Число граней
		int stackCount //Число секций
	);
	void genTorus(
		std::vector<GLuint>& outIndexes, //Выходной массив индексов
		std::vector < glm::vec3 >& outVertices, //Выходной массив координат
		std::vector < glm::vec2 >& outTextures, //Выходной массив текстурных координат
		std::vector < glm::vec3 >& outNormals, //Выходной массив векторов нормалей
		float outerRadius, //Внешний радиус
		float tubeRadius, //Радиус самого тора
		int sectorCount, //Число граней
		int stackCount //Число секций
	);
	/// <summary>
	/// Функция инициализации всего и создания окна.
	/// </summary>
	/// <param name="w">Ширина окна.</param>
	/// <param name="h">Высота окна.</param>
	/// <param name="Fullscreen">Режим полного экрана. </param>
	/// <param name="title">Window title</param>
	/// <returns>Указатель на созданное окно.</returns>
	static GLFWwindow* Init(int w = 640, int h = 480, bool Fullscreen = false, string title = "test");
	/// <summary>
	/// Function for correct program termination.
	/// </summary>
	static void Clear();
};

