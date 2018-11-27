#include "main.hpp"

#include <iostream>
#include <algorithm>
#include "controller.hpp"
#include "shader.hpp"

using namespace std;
using namespace glm;
void InitGLFW()
{
    // Set window hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "Face", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    // Options
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();
    // Define the viewport dimensions
    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1);

    // Print out some info about the graphics drivers
    std::cout << "--------------------------------------" << endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

void InitController()
{
    if (!Controller::Initialize())
    {
        std::cout << "Unable to initialize camera!" << endl;
    }

    glfwSetKeyCallback(window, Controller::KeyCallback);
    glfwSetCursorPosCallback(window, Controller::MouseCallback);
    glfwSetMouseButtonCallback(window, Controller::MouseButtonCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ReleaseController()
{
    Controller::Release();
}

int main()
{
    // Init GLFW
    InitGLFW();
    InitController();
    // Enable settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Init Model Shader
    Shader modelShader;
    modelShader.Initialize("shaders/model.vert.glsl", "shaders/model.frag.glsl");
    modelShader.Use();

    mat4 projection = perspective(DEFAULT_ZOOM, float(SCREEN_SIZE.x) / float(SCREEN_SIZE.y), NEAR_PLANE, FAR_PLANE);
    // Init FPS Var
    std::cout << "--------------------------------------" << endl;
    std::cout << "Initialize Done." << endl;
    GLfloat deltaTime = 0, currentTime = 0;
    GLfloat startTime = glfwGetTime();
    GLfloat lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // cout << "--------------------------------------" << endl;
        // cout << "FTPS :" << 1.0 / deltaTime << endl;
        glfwPollEvents();
        Controller::Movement(deltaTime);
        view = Controller::GetViewMatrix();
        viewPosition = Controller::GetViewPosition();
        viewDirection = Controller::GetViewDirection();
        mat4 inversed = glm::inverse(projection * view);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // particles2DShader.Use();
        // glBindVertexArray(vao2D);
        // glDrawArrays(GL_POINTS, 0, samples.size());

        glfwSwapBuffers(window);
    }

    ReleaseController();

    glfwTerminate();
    return 0;
}
