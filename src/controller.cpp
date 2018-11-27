#include "controller.hpp"
#include <iostream>

using namespace std;

double Controller::lastX = 720;
double Controller::lastY = 720;
bool Controller::firstMouse = true;
bool Controller::keys[1024] = {false};
Camera *Controller::camera = nullptr;

bool Controller::Initialize()
{
    camera = new Camera();
    if (camera == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Controller::Release()
{
    if (camera != nullptr)
    {
        delete camera;
        camera = nullptr;
    }
}

void Controller::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Controller::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (GLfloat)xpos;
        lastY = (GLfloat)ypos;
        firstMouse = false;
    }

    GLfloat xOffset = (GLfloat)xpos - lastX;
    GLfloat yOffset = lastY - (GLfloat)ypos;

    lastX = (GLfloat)xpos;
    lastY = (GLfloat)ypos;

    camera->ProcessMouseMovement(xOffset, yOffset, true);
}

void Controller::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
}

void Controller::Movement(double deltaTime)
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera->ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera->ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera->ProcessKeyboard(CAM_LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera->ProcessKeyboard(CAM_RIGHT, deltaTime);
}

glm::mat4 Controller::GetViewMatrix()
{
    return camera->GetViewMatrix();
}

glm::vec3 Controller::GetViewPosition()
{
    return camera->GetViewPosition();
}

glm::vec3 Controller::GetViewDirection()
{
    return camera->GetViewDirection();
}
