#include "GLSixthLab.h"

void GLSixthLab::ConfigureScene(int scene)
{
	models.clear();
	colors.clear();
	indexes.clear();
	vertices.clear();
	textures.clear();
	normals.clear();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);//Режим тестирования буфера глубины
	glDepthFunc(GL_LESS);//Метод для буфера глубины
	switch (scene)
	{
		case 0:
		{
			FirstTask();
		}
		break;
		case 1:
		{
			SecondTask();
		}
		break;
		case 2:
		{
			ThirdTask();
		}
		break;
		case 3:
		{
			FourthTask();
		}
		break;
		case 4:
		{
			FifthTask();
		}
		break;
	}
}

void GLSixthLab::Render()
{
	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	if (currentOffset + moveSpeed * deltaTime > maxOffset)
	{
		currentOffset = maxOffset;
		moveSpeed = -moveSpeed;
	}
	else if (currentOffset + moveSpeed * deltaTime < minOffset)
	{
		currentOffset = minOffset;
		moveSpeed = -moveSpeed;
	}
	else
	{
		currentOffset += moveSpeed * deltaTime;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, winWidth, winHeight);

	if (currentScene == 0)
	{
		for (auto& model : models)
		{
			model->render();
		}
	}
	else if(currentScene != 4)
	{
		for (auto& model : models)
		{
			model->renderWithLights(light, cameraPos);
		}
	}
	else
	{
		ConfigureScene(4);
		for (auto& model : models)
		{
			model->renderWithLights(light, cameraPos);
		}
	}
	glfwSwapBuffers(window);
}

void GLSixthLab::FirstTask()
{
	glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0, 0));
	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));

	GLUtils::genSphere(indexes, vertices, textures, normals, radius, resolution, resolution);
	GLModel* sphere_1 = new GLModel(window);
	GLModel* sphere_2 = new GLModel(window);

	for (int i = 0; i < vertices.size(); i++)
	{
		colors.push_back({ 1.0f, 0.0f, 0.0f });
	}

	sphere_1->setShaderProgram(n_shaderID);
	sphere_1->loadCoords(vertices.data(), vertices.size());
	sphere_1->loadIndexes(indexes.data(), indexes.size());
	sphere_1->loadColors(colors.data(), colors.size());
	sphere_1->setMmatrix(view1);
	sphere_1->setPmatrix(projMatrix);
	sphere_1->setVmatrix(viewMatrix);

	sphere_2->setShaderProgram(n_shaderID);
	sphere_2->loadCoords(vertices.data(), vertices.size());
	sphere_2->loadIndexes(indexes.data(), indexes.size());
	sphere_2->loadColors(colors.data(), colors.size());
	sphere_2->setMmatrix(view2);
	sphere_2->setPmatrix(projMatrix);
	sphere_2->setVmatrix(viewMatrix);

	models.push_back(sphere_1);
	models.push_back(sphere_2);
}

void GLSixthLab::SecondTask()
{
	GLUtils::genSphere(indexes, vertices, textures, normals, radius, resolution, resolution);

	GLModel * sphere_1 = new GLModel(window);
	GLModel * sphere_2 = new GLModel(window);
	glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0, 0));
	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));

	SetupModel(sphere_1, view1, nullptr);
	SetupModel(sphere_2, view2, nullptr);

	light = new LightsInfo();
	initDir();

	models.push_back(sphere_1);
	models.push_back(sphere_2);
}

void GLSixthLab::ThirdTask()
{
	GLUtils::genSphere(indexes, vertices, textures, normals, radius, resolution, resolution);

	GLModel* sphere_1 = new GLModel(window);
	GLModel* sphere_2 = new GLModel(window);
	glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0, 0));
	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));

	SetupModel(sphere_1, view1, materials["Bronze"]);
	SetupModel(sphere_2, view2, materials["White rubber"]);

	light = new LightsInfo();
	initDir();

	models.push_back(sphere_1);
	models.push_back(sphere_2);
}

void GLSixthLab::FourthTask()
{
	GLUtils::genSphere(indexes, vertices, textures, normals, radius, resolution, resolution);

	GLModel* sphere_1 = new GLModel(window);
	GLModel* sphere_2 = new GLModel(window);
	glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0, 0));
	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));

	SetupModel(sphere_1, view1, materials["Bronze"]);
	SetupModel(sphere_2, view2, materials["White rubber"]);

	light = new LightsInfo();
	initDir();
	initPS();

	GLUtils::genSphere(indexes, vertices, textures, normals, 0.5, 10, 10);
	GLModel * lightIndicator = AddIndicator({ 0,0,0 });
	GLModel * lightIndicator2 = AddIndicator({ -20,0,0 });
	GLModel * lightIndicator3 = AddIndicator({ 0,15.0f,0 });

	models.push_back(sphere_1);
	models.push_back(sphere_2);
	models.push_back(lightIndicator);
	models.push_back(lightIndicator2);
	models.push_back(lightIndicator3);
}

void GLSixthLab::FifthTask()
{
	GLUtils::genSphere(indexes, vertices, textures, normals, radius, resolution, resolution);

	GLModel* sphere_1 = new GLModel(window);
	GLModel* sphere_2 = new GLModel(window);
	glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0 + currentOffset, 0));
	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0 + currentOffset));

	SetupModel(sphere_1, view1, materials["Bronze"]);
	SetupModel(sphere_2, view2, materials["White rubber"]);

	light = new LightsInfo();
	initDir();
	initPS();

	GLUtils::genSphere(indexes, vertices, textures, normals, 0.5, 10, 10);
	GLModel * lightIndicator = AddIndicator({ 0,0,0 });
	GLModel * lightIndicator2 = AddIndicator({ -20,0,0 });
	GLModel * lightIndicator3 = AddIndicator({ 0,15.0f,0 });

	models.push_back(sphere_1);
	models.push_back(sphere_2);
	models.push_back(lightIndicator);
	models.push_back(lightIndicator2);
	models.push_back(lightIndicator3);
}

GLModel* GLSixthLab::AddIndicator(glm::vec3 pos)
{
	colors.clear();
	GLModel * indicator = new GLModel(window);

	for (int i = 0; i < vertices.size(); i++)
	{
		colors.push_back({ 1.0f, 0.95f, 0.2f });
	}

	indicator->setShaderProgram(n_shaderID);
	indicator->loadCoords(vertices.data(), vertices.size());
	indicator->loadIndexes(indexes.data(), indexes.size());
	indicator->loadColors(colors.data(), colors.size());
	indicator->setMmatrix(glm::translate(glm::mat4(1.0f), pos));
	indicator->setPmatrix(projMatrix);
	indicator->setVmatrix(viewMatrix);

	return indicator;
}

void GLSixthLab::SetupModel(GLModel* model, glm::mat4 modelMatrix, Material* material)
{
	model->setShaderProgram(l_shaderID);
	model->loadCoords(vertices.data(), vertices.size());
	model->loadIndexes(indexes.data(), indexes.size());
	model->loadNormals(normals.data(), normals.size());
	if (material)
	{
		model->setMaterial(material);
	}
	model->setMmatrix(modelMatrix);
	model->setPmatrix(projMatrix);
	model->setVmatrix(viewMatrix);
}

void GLSixthLab::initDir()
{
	light->dirLight.ambient = glm::vec3(0.1f);
	light->dirLight.diffuse = glm::vec3(0.4f);
	light->dirLight.specular = glm::vec3(0.1f);
	light->dirLight.direction = glm::vec3(-5, 0, 5);
	light->numPLights = 0;
	light->numSLights = 0;
}

void GLSixthLab::initPS()
{
	light->numPLights = 3;
	light->numSLights = 1;

	light->pointLights[0].ambient = glm::vec3(0.6f, 0.3f, 0.1f);
	light->pointLights[0].diffuse = glm::vec3(0.6f);
	light->pointLights[0].specular = glm::vec3(0.6f);
	light->pointLights[0].position = glm::vec3(0.0f);
	light->pointLights[0].constant = 1;
	light->pointLights[0].linear = 0.22;
	light->pointLights[0].quadratic = 0.2;

	light->pointLights[1].ambient = glm::vec3(1);
	light->pointLights[1].diffuse = glm::vec3(1);
	light->pointLights[1].specular = glm::vec3(1);
	light->pointLights[1].position = glm::vec3(-20.0f, 0.0f, 0.0f);
	light->pointLights[1].constant = 1;
	light->pointLights[1].linear = 0.02;
	light->pointLights[1].quadratic = 0.2;

	light->pointLights[2].ambient = glm::vec3(1);
	light->pointLights[2].diffuse = glm::vec3(1);
	light->pointLights[2].specular = glm::vec3(1);
	light->pointLights[2].position = glm::vec3(0.0f, 15.0f, 0.0f);
	light->pointLights[2].constant = 1;
	light->pointLights[2].linear = 0.02;
	light->pointLights[2].quadratic = 0.2;

	light->spotLights[0].ambient = glm::vec3(0.4f);
	light->spotLights[0].diffuse = glm::vec3(1);
	light->spotLights[0].specular = glm::vec3(1);
	light->spotLights[0].direction = glm::vec3(0.0f, 0.0f, 1.0f);
	light->spotLights[0].position = cameraPos;
	light->spotLights[0].cutOff = cos(PI / 4);
	light->spotLights[0].outerCutOff = cos(PI / 3.5);
	light->spotLights[0].constant = 1;
	light->spotLights[0].linear = 0.02;
	light->spotLights[0].quadratic = 0.2;
}


void GLSixthLab::Init(GLFWwindow* window)
{
	GLController::Init(window);
	this->sceneCount = SCENE_COUNT;

	glPointSize(10);
	glLineWidth(5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

	n_shaderID = GLUtils::CreateShaderProgram("matrix_vs.glsl", "mono_fs.glsl", "vertex_color");
	l_shaderID = GLUtils::CreateShaderProgram("l_vs.glsl", "lighting_fs.glsl", "vertex_normal");

	projMatrix = glm::perspective(
		glm::radians(60.0f),
		(float)winWidth / (float)winHeight,
		0.1f, 
		100.0f 
	);

	cameraPos = glm::vec3(0.0f, 0.0f, -30.0f);
	viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	materials["Bronze"] = new Material();
	materials["Bronze"]->ambient = glm::vec3(0.2125f, 0.1275f, 0.054f);
	materials["Bronze"]->diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
	materials["Bronze"]->specular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
	materials["Bronze"]->shininess = 0.2f * 256;

	materials["White rubber"] = new Material();
	materials["White rubber"]->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	materials["White rubber"]->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	materials["White rubber"]->specular = glm::vec3(0.7f, 0.7f, 0.7f);
	materials["White rubber"]->shininess = 0.078125f * 16;

	ConfigureScene(0);
}

GLSixthLab::GLSixthLab()
{

}
