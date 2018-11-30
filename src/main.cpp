#include "main.hpp"

#include <iostream>
#include <algorithm>
#include "controller.hpp"
#include "EulerOperationTest.hpp"

using namespace std;
using namespace glm;

int main()
{
    // Init GLFW
    InitGLFW();
    InitController();
    // Enable settings
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2, 0.2, 0.4, 1.0);

    // Init FPS Var
    std::cout << "--------------------------------------" << endl;
    std::cout << "Initialize Done." << endl;


    vector<Solid*> solidList;
    Solid *solidZero = CreateZero();
    solidList.push_back(solidZero);
    Solid *solidOne = CreateOne();
    solidList.push_back(solidOne);
    Solid *solidTwo = CreateTwo();
    solidList.push_back(solidTwo);
    Solid *solidEight = CreateEight();
    solidList.push_back(solidEight);

    GLfloat deltaTime = 0, currentTime = 0;
    GLfloat startTime = glfwGetTime();
    GLfloat lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        Solid *drawSolid = solidList[Controller::count % solidList.size()];
        glfwPollEvents();
        GLfloat newTime = glfwGetTime();
        Controller::Movement(newTime - lastTime);
        lastTime = newTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        glViewport(0, 0, SCREEN_SIZE.x / 2, SCREEN_SIZE.y);
        
        // Perspective
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, SCREEN_SIZE.x / 2.0 / SCREEN_SIZE.y, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // Reset the model-view matrix
        glTranslatef(0.0f, 0.0f, -10.0f);

        glRotatef(Controller::zAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(Controller::yAngle, 1.0f, 0.0f, 1.0f);

        glRotatef(180.0, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0, 1.0f, 0.0f, 0.0f);

        DrawSolid(drawSolid);

        glViewport(SCREEN_SIZE.x / 2, 0, SCREEN_SIZE.x / 2, SCREEN_SIZE.y);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, SCREEN_SIZE.x / 2.0 / SCREEN_SIZE.y, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // Reset the model-view matrix
        glTranslatef(0.0f, 0.0f, -10.0f);
        

        glRotatef(Controller::zAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(Controller::yAngle, 1.0f, 0.0f, 1.0f);

        glRotatef(180.0, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0, 1.0f, 0.0f, 0.0f);
        DrawSolid(drawSolid, true);

        glfwSwapBuffers(window);
    }

    ReleaseController();

    glfwTerminate();
    return 0;
}

int InitGLFW()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    // glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // Create window
    window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "Euler Operation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    // Windowed
    glfwMakeContextCurrent(window);
    // Options
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();
    // Define the viewport dimensions
    // glEnable(GL_MULTISAMPLE);
    // glfwSwapInterval(1);

    // Print out some info about the graphics drivers
    std::cout << "--------------------------------------" << endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    return 0;
}

void InitController()
{
    if (!Controller::Initialize())
    {
        std::cout << "Unable to initialize camera!" << endl;
    }

    glfwSetKeyCallback(window, Controller::KeyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ReleaseController()
{
    Controller::Release();
}
