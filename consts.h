#pragma once
#include <glm/glm.hpp>
// Global variables
#define PI 3.14159265358979323846f

#define CENTER_X (float)winWidth / 2.0f
#define CENTER_Y (float)winHeight / 2.0f

#define RIGHT (float)winWidth
#define LEFT 0.0f
#define TOP (float)winHeight
#define BOTTOM 0.0f

#define ASPECT_RATIO (float)winWidth / (float)winHeight
/// <summary>
/// window width
/// </summary>
extern int winWidth;
/// <summary>
/// window height
/// </summary>
extern int winHeight;
/// <summary>
/// Identity matrix
/// </summary>
extern const glm::mat4 WorldMatrix;
/// <summary>
/// rotation direction
/// </summary>
extern bool rotationmode;

