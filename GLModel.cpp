#include "GLModel.h"

void GLModel::applyMaterial()
{
	if (material)
	{
		GLuint matAmbientLoc = glGetUniformLocation(shaderProgramID, "material.ambient");
		GLuint matDiffuseLoc = glGetUniformLocation(shaderProgramID, "material.diffuse");
		GLuint matSpecularLoc = glGetUniformLocation(shaderProgramID, "material.specular");
		GLuint matShininessLoc = glGetUniformLocation(shaderProgramID, "material.shininess");

		glUniform3fv(matAmbientLoc, 1, &material->ambient[0]);
		glUniform3fv(matDiffuseLoc, 1, &material->diffuse[0]);
		glUniform3fv(matSpecularLoc, 1, &material->specular[0]);
		glUniform1f(matShininessLoc, material->shininess);


		//vector<GLfloat> mat;
		//for (int i = 0; i < 3; i++) {
		//	mat.push_back(material->ambient[0]);
		//}
		//mat.push_back(1.0f);
		//glMaterialfv(GL_FRONT, GL_AMBIENT, mat.data());

		//mat.clear();
		//for (int i = 0; i < 3; i++) {
		//	mat.push_back(material->diffuse[0]);
		//}
		//mat.push_back(1.0f);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.data());

		//mat.clear();
		//for (int i = 0; i < 3; i++) {
		//	mat.push_back(material->specular[0]);
		//}
		//mat.push_back(1.0f);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat.data());
		//glMaterialf(GL_FRONT, GL_SHININESS, material->shininess * 128.0);
	}
}

void GLModel::applyMatrix()
{
	//привязка матрицы преобразований
	GLuint pMatrixID = glGetUniformLocation(shaderProgramID, "projection");
	GLuint vMatrixID = glGetUniformLocation(shaderProgramID, "view");
	GLuint mMatrixID = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(pMatrixID, 1, GL_FALSE, &Pmatrix[0][0]);
	glUniformMatrix4fv(vMatrixID, 1, GL_FALSE, &Vmatrix[0][0]);
	glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &Mmatrix[0][0]);
}

void GLModel::applyLights(LightsInfo* lights, glm::vec3 cameraPosition)
{
	GLuint camposLoc = glGetUniformLocation(shaderProgramID, "campos");

	glUniform3fv(camposLoc, 1, &cameraPosition[0]);

	GLuint dirAmbientLoc = glGetUniformLocation(shaderProgramID, "lights.dirLight.ambient");
	GLuint dirDiffuseLoc = glGetUniformLocation(shaderProgramID, "lights.dirLight.diffuse");
	GLuint dirSpecularLoc = glGetUniformLocation(shaderProgramID, "lights.dirLight.specular");
	GLuint dirDirectionLoc = glGetUniformLocation(shaderProgramID, "lights.dirLight.direction");


	glUniform3fv(dirAmbientLoc, 1, &lights->dirLight.ambient[0]);
	glUniform3fv(dirDiffuseLoc, 1, &lights->dirLight.diffuse[0]);
	glUniform3fv(dirSpecularLoc, 1, &lights->dirLight.specular[0]);
	glUniform3fv(dirDirectionLoc, 1, &lights->dirLight.direction[0]);

	GLuint pCountLoc = glGetUniformLocation(shaderProgramID, "lights.numPLights");
	GLuint sCountLoc = glGetUniformLocation(shaderProgramID, "lights.numSLights");

	glUniform1i(pCountLoc, lights->numPLights);
	glUniform1i(sCountLoc, lights->numSLights);

	

	for (int i = 0; i < lights->numPLights; i++)
	{
		string shaderVarName = "lights.pointLights[" + to_string(i) + "].";

		GLuint pointLightPosition = glGetUniformLocation(shaderProgramID, (shaderVarName + "position").c_str());
		GLuint pointLightAmbient = glGetUniformLocation(shaderProgramID, (shaderVarName + "ambient").c_str());
		GLuint pointLightDiffuse = glGetUniformLocation(shaderProgramID, (shaderVarName + "diffuse").c_str());
		GLuint pointLightSpecular = glGetUniformLocation(shaderProgramID, (shaderVarName + "specular").c_str());


		GLuint pointLightConstant = glGetUniformLocation(shaderProgramID, (shaderVarName + "constant").c_str());
		GLuint pointLightLinear = glGetUniformLocation(shaderProgramID, (shaderVarName + "linear").c_str());
		GLuint pointLightQuadratic = glGetUniformLocation(shaderProgramID, (shaderVarName + "quadratic").c_str());
		

		glUniform3fv(pointLightPosition, 1, &lights->pointLights[i].position[0]);
		glUniform3fv(pointLightAmbient, 1, &lights->pointLights[i].ambient[0]);
		glUniform3fv(pointLightDiffuse, 1, &lights->pointLights[i].diffuse[0]);
		glUniform3fv(pointLightSpecular, 1, &lights->pointLights[i].specular[0]);

		glUniform1f(pointLightConstant, lights->pointLights[i].constant);
		glUniform1f(pointLightLinear, lights->pointLights[i].linear);
		glUniform1f(pointLightQuadratic, lights->pointLights[i].quadratic);
	}

	for (int i = 0; i < lights->numSLights; i++)
	{
		string shaderVarName = "lights.spotLights[" + to_string(i) + "].";

		GLuint spotLightPosition = glGetUniformLocation(shaderProgramID, (shaderVarName + "position").c_str());
		GLuint spotLightAmbient = glGetUniformLocation(shaderProgramID, (shaderVarName + "ambient").c_str());
		GLuint spotLightDiffuse = glGetUniformLocation(shaderProgramID, (shaderVarName + "diffuse").c_str());
		GLuint spotLightSpecular = glGetUniformLocation(shaderProgramID, (shaderVarName + "specular").c_str());
		GLuint spotLightDirection = glGetUniformLocation(shaderProgramID, (shaderVarName + "direction").c_str());


		GLuint spotLightConstant = glGetUniformLocation(shaderProgramID, (shaderVarName + "constant").c_str());
		GLuint spotLightLinear = glGetUniformLocation(shaderProgramID, (shaderVarName + "linear").c_str());
		GLuint spotLightQuadratic = glGetUniformLocation(shaderProgramID, (shaderVarName + "quadratic").c_str());
		GLuint spotLightCutoff = glGetUniformLocation(shaderProgramID, (shaderVarName + "cutOff").c_str());
		GLuint spotLightOuterCutOff = glGetUniformLocation(shaderProgramID, (shaderVarName + "outerCutOff").c_str());


		glUniform3fv(spotLightPosition, 1, &lights->spotLights[i].position[0]);
		glUniform3fv(spotLightAmbient, 1, &lights->spotLights[i].ambient[0]);
		glUniform3fv(spotLightDiffuse, 1, &lights->spotLights[i].diffuse[0]);
		glUniform3fv(spotLightSpecular, 1, &lights->spotLights[i].specular[0]);
		glUniform3fv(spotLightDirection, 1, &lights->spotLights[i].direction[0]);

		glUniform1f(spotLightConstant, lights->spotLights[i].constant);
		glUniform1f(spotLightLinear, lights->spotLights[i].linear);
		glUniform1f(spotLightQuadratic, lights->spotLights[i].quadratic);
		glUniform1f(spotLightCutoff, lights->spotLights[i].cutOff);
		glUniform1f(spotLightOuterCutOff, lights->spotLights[i].outerCutOff);
	}
}

size_t GLModel::getVertexCount()
{
	return vertexCount;
}

void GLModel::setVmatrix(glm::mat4 Vmatrix)
{
	this->Vmatrix = Vmatrix;
}

void GLModel::setPmatrix(glm::mat4 Pmatrix)
{
	this->Pmatrix = Pmatrix;
}

void GLModel::setMmatrix(glm::mat4 Mmatrix)
{
	this->Mmatrix = Mmatrix;
}

void GLModel::setMaterial(Material * material)
{
	this->material = material;
}

void GLModel::setMode(GLuint mode)
{
	this->mode = mode;
}

void GLModel::setShaderProgram(GLuint shaderProgramID)
{
	this->shaderProgramID = shaderProgramID;
}

void GLModel::render()
{
	//Выбираем шейдерную программу
	glUseProgram(shaderProgramID);

	applyMatrix();

	glBindVertexArray(vaoID);

	//Если индексы есть - рисуем по ним
	if (indexCount > 0)
		glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, vertexCount);
}

void GLModel::renderWithLights(LightsInfo* lights, glm::vec3 cameraPosition)
{
	//Выбираем шейдерную программу
	glUseProgram(shaderProgramID);

	applyMatrix();
	applyMaterial();
	applyLights(lights, cameraPosition);

	glBindVertexArray(vaoID);

	//Если индексы есть - рисуем по ним
	if (indexCount > 0)
		glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, vertexCount);
}

void GLModel::loadCoords(glm::vec3* verteces, size_t count)
{
	//Сохранение размера массива
	vertexCount = count;
	//Создание VBO
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3),verteces, GL_STATIC_DRAW);
	
	//Так как VAO уже создан, то можно сразу связать с ним
	glBindVertexArray(vaoID);
	//Собственно связь
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Подключение атрибута
	glEnableVertexAttribArray(0);
}

void GLModel::loadNormals(glm::vec3* normals, size_t count)
{
	GLuint normals_vbo = 0;
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), normals,
		GL_STATIC_DRAW);
	glBindVertexArray(vaoID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
}

void GLModel::loadColors(glm::vec3* colors, size_t count)
{
	//Размер сохранять не требуется – важно только число вершин
	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), colors,
		GL_STATIC_DRAW);
	glBindVertexArray(vaoID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

}

void GLModel::loadIndexes(GLuint* indices, size_t count)
{
	indexCount = count;
	glBindVertexArray(vaoID);
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer); // Генерация одного объекта буфера вершин
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer); //Привязка элементного буфера
	//Загрузка индексов в используемый элементный буфер
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}


