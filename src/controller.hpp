#pragma once

#include "camera.hpp"

class Controller {
public:
    static bool Initialize();
    static void Release();

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void Movement(double deltaTime);
    
    static glm::mat4 GetViewMatrix();
    static glm::vec3 GetViewPosition();
    static glm::vec3 GetViewDirection();

private:
    static bool firstMouse;
    static bool keys[1024];
    static double lastX, lastY;
    static Camera *camera;
};