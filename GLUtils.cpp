#include "GLUtils.h"
#include "consts.h"
#include "callbacks.h"

vector<glm::vec3> GLUtils::Normalize(vector<glm::vec3> vertexes)
{
    for (int i = 0; i < vertexes.size(); i++)
    {
        vertexes[i].x = vertexes[i].x / (float)winWidth * (float)winHeight;
    }

    return vertexes;
}

string GLUtils::LoadShader(const char* filename)
{
    string shader;
    ifstream file(filename, ios::in);
    if (file.is_open())
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        shader = sstr.str();
        file.close();
    }
    return shader;
}

GLuint GLUtils::CreateShaderProgram(const char* vertexFilename, const char* fragmentFilename, string attr)
{
    // ���������� ��� ��������� ���������� ���������
    GLint result = GL_FALSE;
    int infoLogLength;
    //�������� ��������� ���������
    GLuint shaderProgramID = glCreateProgram();
    //�������� ������� �������� �� ������
    string vstext = GLUtils::LoadShader(vertexFilename);
    const char* vertex_shader = vstext.c_str();
    string fstext = GLUtils::LoadShader(fragmentFilename);
    const char* fragment_shader = fstext.c_str();

    //�������� ���������� �������
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    //���������� � ����������� ��������
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLint success;
    GLchar infoLog[512];

    // �������� ���������� ���������� �������
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // �������� ���������� ������������ �������
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //������ ���������
    glAttachShader(shaderProgramID, vs);
    glAttachShader(shaderProgramID, fs);

    //������ ������ � ��� ����� ����������� �������� ������� ���������� � �������� �� ���������� ������� ������
    //��� ����� ������� � ��������� ������� ��� ������� ���������������.
    //������ ��� ��� ��� ������, �� ��������� ���
    glBindAttribLocation(shaderProgramID, 0, "vertex_position");
    glBindAttribLocation(shaderProgramID, 1, attr.c_str());

    //���������� ��������� ���������
    glLinkProgram(shaderProgramID);

    // �������� �������� ���������
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgramID;
}

vector<glm::vec3> GLUtils::GeneratePolygon(int n, int scaleX, int scaleY, float offsetX, float offsetY, float rotation)
{
    vector<glm::vec3> points;
    float offsetAngle = (360 / (float)n) / 180 * PI;

    for (int i = 0; i < n; i++)
    {
        float x = scaleX * cos(offsetAngle * i + rotation) + offsetX;
        float y = scaleY * sin(offsetAngle * i + rotation) + offsetY;
        points.push_back({ x, y, 0.0f });
    }

    return points;
}

vector<glm::vec3> GLUtils::TranslateXY(vector<glm::vec3> vertexes, float x, float y)
{
    vector<glm::vec3> newVector = vertexes;

    for (int i = 0; i < newVector.size(); i++)
    {
        newVector[i].x += x;
        newVector[i].y += y;
    }

    return newVector;
}

bool GLUtils::loadOBJ(const char* path, vector<glm::vec3>& outVertices, vector<glm::vec2>& outTextures, vector<glm::vec3>& outNormals)
{
    //��������� ������� ��� �������� �������� � �������� �� �����
    std::vector< unsigned int > vertexIndices, vtIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_textures;
    std::vector< glm::vec3 > temp_normals;
    //������ ��� �������� ������� �� �����
    string buf;
    //�����, �������� ���������� �����
    std::stringstream sstr;
    //���������� ��� ���������� ������ � ����������� ������ ������ � �����
    bool cont = false;

    //���������� �����
    ifstream file(path, ios::in);
    if (file.is_open())
    {
        sstr << file.rdbuf();
        file.close();
    }
    else
        return false;

    //������� �������� ��������
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();
    //������� ������� ����� �� �����
    while (cont || sstr >> buf)
    {
        cont = false;

        //��������� ���������
        if (buf == "v")
        {
            glm::vec3 vertex;
            sstr >> vertex.x;
            sstr >> vertex.y;
            sstr >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        //��������� ���������� ���������
        else if (buf == "vt")
        {
            glm::vec2 texture;
            sstr >> texture.x;
            sstr >> texture.y;
            temp_textures.push_back(texture);
        }
        else if (buf == "vn")
        {
            glm::vec3 normal;
            sstr >> normal.x;
            sstr >> normal.y;
            sstr >> normal.z;
            temp_normals.push_back(normal);
        }
        //��������� ������
        else if (buf == "f")
        {
            //��������� ������� ��� �������� ���������� � �����
            vector<string> vertexes;
            vector<int> vertindexes;
            while (!cont)
            {
                //����������� �����
                sstr >> buf;
                //���� ����� �������� ������ � ������� � ��� ������������ � ������
                    if (buf.find('/') != string::npos)
                        vertexes.push_back(buf);
                //���� ����� � ������ ��������� ������, �� ����������� � ���������� ��������� �����
                    else
                    {
                        //��� ������ �� ���������� ������ ������������ �������������
                        for (string vert : vertexes)
                        {
                            std::replace(vert.begin(), vert.end(), '/', ' ');
                            std::stringstream tmpstream(vert);
                            int v, vt, n;
                            tmpstream >> v;
                            tmpstream >> vt;
                            tmpstream >> n;
                            //������� ��������� � ��������� ������
                            vertindexes.push_back(v);
                            vertindexes.push_back(vt);
                            vertindexes.push_back(n);
                        }
                        //������ ��� ������� ��������� � ������� ��������
                        for (int i = 0; i < 3; i++)
                        {
                            vertexIndices.push_back(vertindexes[i * 3 + 0]);
                            vtIndices.push_back(vertindexes[i * 3 + 1]);
                            normalIndices.push_back(vertindexes[i * 3 + 2]);
                        }
                        //������ ������� � ���� ��� �������� �������, ���� � �� �������
                        //�� ���� ������������� �� ����� ������������� � ����� �������������
                            size_t tmpsize = vertexes.size();
                        if (tmpsize > 3)
                        {
                            //��� ������ �� ������ ����������� ��� �������, ���������� �����������
                                for (int i = 3; i < tmpsize; i++)
                                {
                                    vertexIndices.push_back(vertindexes[0]);
                                    vtIndices.push_back(vertindexes[1]);
                                    normalIndices.push_back(vertindexes[2]);
                                    vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
                                    vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
                                    normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
                                    vertexIndices.push_back(vertindexes[i * 3 + 0]);
                                    vtIndices.push_back(vertindexes[i * 3 + 1]);
                                    normalIndices.push_back(vertindexes[i * 3 + 2]);
                                }
                        }
                        //����� �� ��������� ��������� �����, �������� ���� � ���, ��� �� �������
                        cont = true;
                    }
            }
        }
    }

    // ������ ��������� �������� �������� � �������� �������� ��������
        // ��� ������ ������� � ������� ��������, ���������������
        // ������� ��� ��������� �������� ��������� � �������� ������
        size_t tmpsize = vertexIndices.size();
    for (unsigned int i = 0; i < tmpsize; i++)
    {
        //���� ������, ��� ������� � ����� ���������� � 1!
        glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
        outVertices.push_back(vertex);
        glm::vec3 normal = temp_normals[normalIndices[i] - 1];
        outNormals.push_back(normal);
        glm::vec2 vt = temp_textures[vtIndices[i] - 1];
        outTextures.push_back(vt);
    }
    return true;
}

 void GLUtils::genSphere(
    std::vector<GLuint>& outIndexes, //�������� ������ ��������
    std::vector < glm::vec3 >& outVertices, //�������� ������ ���������
    std::vector < glm::vec2 >& outTextures, //�������� ������ ���������� ���������
    std::vector < glm::vec3 >& outNormals, //�������� ������ �������� ��������
    float radius, //������ �����
    int sectorCount, //����� ����������
    int stackCount //����� ����������
)
{
    //������� �������� ��������
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();
    //��������������� ���������� ��� �������� ������������� ������
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;
    float sectorStep = 2.0f * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    //���� �� ������ ���������
    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep; // ������� �� PI/2 � �� -PI/2
        xy = radius * cosf(stackAngle); // r * cos(u)
        z = radius * sinf(stackAngle); // r * sin(u)
        // �� ������ ��������� ����������� (sectorCount+1) ������
        // ��� ������ � ��������� ��������� ������� � �������, �� ���������� ���������� ����������
            for (int j = 0; j <= sectorCount; ++j)
            {
                sectorAngle = j * sectorStep; // �� 0 �� 2PI
                // ������������� ���������� (x, y, z)
                x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
                glm::vec3 vert;
                vert.x = x;
                vert.y = y;
                vert.z = z;
                outVertices.push_back(vert);
                // ������������� ������ ������� (nx, ny, nz)
                nx = x * lengthInv;
                ny = y * lengthInv;
                nz = z * lengthInv;
                glm::vec3 norm;
                norm.x = nx;
                norm.y = ny;
                norm.z = nz;
                outNormals.push_back(norm);
                // ������������� ���������� ���������� (s, t) � ��������� [0, 1]
                s = (float)j / sectorCount;
                t = (float)i / stackCount;
                glm::vec2 vt;
                vt.s = s;
                vt.t = t;
                outTextures.push_back(vt);
            }

            //�� ��������� ���� - ����� ������� ������, �.�. �������
            int k1, k2;
            for (int i = 0; i < stackCount; ++i)
            {
                k1 = i * (sectorCount + 1); // ������ �������� ���������
                k2 = k1 + sectorCount + 1; // ������ ���������� ���������
                for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
                {
                    // ��� ������ � ��������� ��������� �� 1 ������������, ��� ��������� � �� ���
                        // k1 => k2 => k1+1
                        if (i != 0)
                        {
                            outIndexes.push_back(k1);
                            outIndexes.push_back(k2);
                            outIndexes.push_back(k1 + 1);
                        }
                    // k1+1 => k2 => k2+1
                    if (i != (stackCount - 1))
                    {
                        outIndexes.push_back(k1 + 1);
                        outIndexes.push_back(k2);
                        outIndexes.push_back(k2 + 1);
                    }
                }
            }
    }
}

void GLUtils::genCylinder(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float baseRadius, float topRadius, float height, int sectorCount, int stackCount)
{
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();
    float radius;
    // ����� ��������������� �������
    std::vector<glm::vec3> unitVertices; //= getUnitCircleVertices(sectorCount);
    // ��������� ��������� ������ ������� ������
    // ����������� ��� ������ ������

    for (int i = 0; i < stackCount + 1; ++i)
    {
        //������ � ������ ������� ������
        float h = 0 + i * (height / stackCount);
        float t = 1.0f - i / stackCount;
        radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);
        // ��� ������� ������� � ������ ������������� �������
        for (int j = 0, k = 0; j <= sectorCount; ++j, k++)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            float uz = unitVertices[k].z;

            // ����������
            glm::vec3 v;
            v.x = ux * radius;
            v.y = uy * radius;
            v.z = h;
            outVertices.push_back(v);
            // ������ �������
            glm::vec3 n;
            n.x = ux;
            n.y = uy;
            n.z = uz;
            outNormals.push_back(n);
            //���������� ����������
            glm::vec2 vt;
            vt.s = (float)j / sectorCount;
            vt.t = t;
            outTextures.push_back(vt);
        }
    }

    // ������ ���� ������������� �������, ����������� ��������� � ��������
        // �� ������� ����������� ������� ������ � ����� ������� ���� ������
    int baseCenterIndex = (int)outVertices.size();
    int topCenterIndex = baseCenterIndex + sectorCount + 1;

    for (int i = 0; i < 2; ++i)
    {
        float h = 0 + i * height;
        float nz = (float)i;
        // ����������� �����
        outVertices.push_back(glm::vec3(0, 0, h));
        outNormals.push_back(glm::vec3(0, 0, nz));
        outTextures.push_back(glm::vec2(0.5, 0.5));
        radius = i ? topRadius : baseRadius;
        //��� ������ ������� � ������� ������������� ���������
        for (int j = 0, k = 0; j < sectorCount; ++j, k++)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            // ����������
            outVertices.push_back(glm::vec3(ux * radius, uy * radius, h));
            // ������ �������
            outNormals.push_back(glm::vec3(0, 0, nz));
            // ���������� ����������
            outTextures.push_back(glm::vec2(-ux * 0.5f + 0.5f, -uy * 0.5f +
                0.5f));
        }
    }
    //������ ������ ��������
    int k1 = 0;
    int k2 = sectorCount + 1;
    // ������� �����
    for (int i = 0; i < sectorCount * (stackCount + 2); ++i, ++k1, ++k2)
    {
        // �� ������ ������ �� ��� �����
        // k1 => k1+1 => k2
        outIndexes.push_back(k1);
        outIndexes.push_back(k1 + 1);
        outIndexes.push_back(k2);

        // k2 => k1+1 => k2+1
        outIndexes.push_back(k2);
        outIndexes.push_back(k1 + 1);
        outIndexes.push_back(k2 + 1);
    }
    // ������ ������� ��������� � ��������
    for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            outIndexes.push_back(baseCenterIndex);
            outIndexes.push_back(k + 1);
            outIndexes.push_back(k);
        }
        else
        {
            outIndexes.push_back(baseCenterIndex);
            outIndexes.push_back(baseCenterIndex + 1);
            outIndexes.push_back(k);
        }
    }
    for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            outIndexes.push_back(topCenterIndex);
            outIndexes.push_back(k);
            outIndexes.push_back(k + 1);
        }
        else // �������� ��������� �����������
        {
            outIndexes.push_back(topCenterIndex);
            outIndexes.push_back(k);
            outIndexes.push_back(topCenterIndex + 1);
        }
    }
}

void GLUtils::genTorus(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float outerRadius, float tubeRadius, int sectorCount, int stackCount)
{
    //������� �������� ��������
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();
    float du = 2 * PI / stackCount;
    float dv = 2 * PI / sectorCount;
    //��������� ������ ��� ������ ������
    for (size_t i = 0; i < stackCount; i++)
    {
        float u = i * du;
        //��������� ��� ������� ������� � ������
        for (size_t j = 0; j <= sectorCount; j++)
        {
            float v = (j % sectorCount) * dv;
            for (size_t k = 0; k < 2; k++)
            {
                float uu = u + k * du;
                // ����������
                float x = (outerRadius + tubeRadius * cos(v)) * cos(uu);
                float y = (outerRadius + tubeRadius * cos(v)) * sin(uu);
                float z = tubeRadius * sin(v);
                outVertices.push_back(glm::vec3(x, y, z));
                // ������ �������
                float nx = cos(v) * cos(uu);
                float ny = cos(v) * sin(uu);
                float nz = sin(v);
                outNormals.push_back(glm::vec3(nx, ny, nz));
                // ���������� ����������
                float tx = uu / (2 * PI);
                float ty = v / (2 * PI);
                outTextures.push_back(glm::vec2(tx, ty));
            }

            v += dv;
        }
    }
    // ������ �������� � ��� ���� �����.
    // ���������� ����� ���� ������������ ��� ����� �������������
    // ������ �� ����� �� ���� ������������� � ����� �������������
        size_t size = outVertices.size();
        outIndexes.push_back(0);
        outIndexes.push_back(1);
        outIndexes.push_back(2);
        for (int k = 3; k < size; k++)
        {
            outIndexes.push_back(k - 2);
            outIndexes.push_back(k - 1);
            outIndexes.push_back(k);
        }

}

GLFWwindow* GLUtils::Init(int w, int h, bool Fullscreen, string title)
{
    //set global variables
    winWidth = w;
    winHeight = h;
    //create window pointer
    GLFWwindow* window = nullptr;
    //init GLFW
    if (!glfwInit())
    {
        cerr << "ERROR: could not start GLFW3\n";
        exit(-1);
    }

    if (Fullscreen)
    {
        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* vmode = glfwGetVideoMode(mon);
        winWidth = vmode->width;
        winHeight = vmode->height;
        window = glfwCreateWindow(winWidth, winHeight, title.c_str(), mon, NULL);
    }
    else
    {
        window = glfwCreateWindow(winWidth, winHeight, title.c_str(), NULL, NULL);
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    // set context
    glfwMakeContextCurrent(window);
    // connect latest version OpenGL
    glewExperimental = GL_TRUE;

    // init GLEW
    if (glewInit() != GLEW_OK)
    {
        cerr << "ERROR: could not start GLEW\n";
        return nullptr;
    }

    return window;
}

void GLUtils::Clear()
{
    glfwTerminate();
}
