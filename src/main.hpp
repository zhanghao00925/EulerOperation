#pragma once
// STL
#include <vector>
#include <iostream>
#include <algorithm>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DrawOperation.hpp"

using namespace std;
#define PI 3.14159265358979323846

const glm::ivec2 SCREEN_SIZE(1280, 640);
const float FAR_PLANE = 100.0f;
const float NEAR_PLANE = 1.0f;

glm::mat4 view;
glm::vec3 viewPosition;
glm::vec3 viewDirection;

GLFWwindow *window;
int InitGLFW();

void InitController();
void ReleaseController();

Solid* CreateSolid();