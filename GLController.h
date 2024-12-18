#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GLModel.h"
#include "consts.h"
class GLController
{
public:
	enum class SubScenes
	{
		A,
		B,
		C,
		D
	};
protected:
	GLFWwindow* window;
	vector<GLModel *> models;
	int sceneCount;
	int currentScene;
	SubScenes subScene;
	bool isInit;

	GLController() {};
	virtual ~GLController() {};
	GLController(GLController const&) = delete;
	GLController& operator= (GLController const&) = delete;

	virtual void ConfigureScene(int scene) = 0;
	virtual void Render();
public:
	virtual void Init(GLFWwindow* window);
	void Start();

	void ToScene(int scene);
	void ToSubScene(SubScenes subScene);
	void NextScene();
	void PrevScene();
};