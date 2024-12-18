#pragma once
#include "GLController.h"
#include "GLUtils.h"
#include "lights.h"
#include <map>
#define SCENE_COUNT 6
#define N 7
#define LEN_UNIT 100

class GLSixthLab :
    public GLController
{
private:
    GLuint l_shaderID = -1;
    GLuint n_shaderID = -1;

    LightsInfo* light;
    map<string, Material *> materials;

    glm::mat4 projMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 cameraPos;

    vector<glm::vec3> vertices;
    vector<glm::vec2> textures;
    vector<glm::vec3> normals;
    vector<GLuint> indexes;
    vector<glm::vec3> colors;

    float radius = 5.0f;
    int resolution = 30;

    float maxOffset = 10.0f;
    float minOffset = -10.0f;
    float currentOffset = 0.0f;
    float moveSpeed = 5.0f;

    float deltaTime;
    float lastTime;

    GLSixthLab();
    ~GLSixthLab() {};

    void ConfigureScene(int scene) override;
    void Render() override;

    void FirstTask();
    void SecondTask();
    void ThirdTask();
    void FourthTask();
    void FifthTask();

    GLModel * AddIndicator(glm::vec3 pos);
    void SetupModel(GLModel* model, glm::mat4 modelMatrix, Material* material = nullptr);
    void initDir();
    void initPS();

public:
    void Init(GLFWwindow* window) override;
    static GLSixthLab& GetInstance()
    {
        static GLSixthLab instance;
        return instance;
    }
};

