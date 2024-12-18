#include "GLController.h"

void GLController::Start()
{

	while (!glfwWindowShouldClose(window))
	{
		Render();
		glfwPollEvents();
	}
}

void GLController::ToScene(int scene)
{
	if (scene <= sceneCount)
	{
		currentScene = scene;
	}
	std::cout << currentScene << std::endl;
	ConfigureScene(currentScene);
}

void GLController::ToSubScene(SubScenes subScene)
{
	this->subScene = subScene;
	ConfigureScene(currentScene);
}

void GLController::NextScene()
{
	if (currentScene < sceneCount - 1)
	{
		currentScene++;
	}
	else
	{
		currentScene = 0;
	}
	std::cout << currentScene << std::endl;

	ConfigureScene(currentScene);
}

void GLController::PrevScene()
{
	if (currentScene == 0)
	{
		currentScene = sceneCount - 1;
	}
	else
	{
		currentScene--;
	}
	std::cout << currentScene << std::endl;

	ConfigureScene(currentScene);
}

void GLController::Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, winWidth, winHeight);

	for (auto& model : models)
	{
		model->render();
	}
	glfwSwapBuffers(window);
}

void GLController::Init(GLFWwindow* window)
{
	this->window = window;
	currentScene = 0;
	isInit = true;
}
