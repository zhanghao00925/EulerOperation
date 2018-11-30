#include "controller.hpp"
#include <iostream>

using namespace std;

float Controller::yAngle = 0.0;
float Controller::zAngle = 0.0;
unsigned int Controller::count = 0;
bool Controller::keys[1024] = {false};

bool Controller::Initialize()
{
}

void Controller::Release()
{
}

void Controller::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        count++;
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Controller::Movement(float deltaTime)
{
    deltaTime *= 50;
    // Camera controls
    if (keys[GLFW_KEY_W])
        yAngle += 1.0f * deltaTime;
    if (keys[GLFW_KEY_S])
        yAngle -= 1.0f * deltaTime;
    if (keys[GLFW_KEY_A])
        zAngle += 1.0f * deltaTime;
    if (keys[GLFW_KEY_D])
        zAngle -= 1.0f * deltaTime;

}
