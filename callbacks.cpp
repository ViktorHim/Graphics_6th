#include "callbacks.h"

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	winWidth = width;
	winHeight = height;
	cout << "resize" << endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key >= GLFW_KEY_1 && key <= GLFW_KEY_6)
		{
			GLSixthLab::GetInstance().ToScene(key - GLFW_KEY_1);
		}

		if (key >= GLFW_KEY_A && key <= GLFW_KEY_D)
		{
			GLSixthLab::GetInstance().ToSubScene((GLSixthLab::SubScenes)(key - GLFW_KEY_A));
		}

		switch (key)
		{
		case GLFW_KEY_ESCAPE:
		{
			glfwSetWindowShouldClose(window, 1);
		}
		break;
		case GLFW_KEY_LEFT:
		{
			GLSixthLab::GetInstance().PrevScene();
		}
		break;
		case GLFW_KEY_RIGHT:
		{
			GLSixthLab::GetInstance().NextScene();
		}
		break;
		case GLFW_KEY_EQUAL:
		{
		}
		break;
		case GLFW_KEY_MINUS:
		{
		}
		break;
		default:
			break;
		}
	}
}