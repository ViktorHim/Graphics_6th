#pragma once
#include "GLSixthLab.h"
#include <GLFW/glfw3.h>
#include "consts.h"

/// <summary>
/// Resize handler
/// </summary>
/// <param name="window">Window pointer.</param>
/// <param name="width">New window width.</param>
/// <param name="height">New window heigth.</param>
void windowSizeCallback(GLFWwindow* window, int width, int height);
/// <summary>
/// Keyboard handler
/// </summary>
/// <param name="window">Window pointer.</param>
/// <param name="key">Key code.</param>
/// <param name="scancode">Symbol code.</param>
/// <param name="action">Action.</param>
/// <param name="mods">Mods.</param>
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
