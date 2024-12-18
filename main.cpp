#include "GLUtils.h"
#include "GLModel.h"
#include "GLSixthLab.h"

int winWidth;
int winHeight;

const glm::mat4 WorldMatrix = glm::mat4(1.0f);

int main()
{
	GLFWwindow* window = GLUtils::Init(1920, 1080, false, "6th");
	if (window == nullptr)
	{
		GLUtils::Clear();
		return -1;
	}

	GLSixthLab::GetInstance().Init(window);
	GLSixthLab::GetInstance().Start();
	
	GLUtils::Clear();
	return 0;
}