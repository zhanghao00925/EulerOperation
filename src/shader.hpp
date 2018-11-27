#pragma once

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader() {}
    void Initialize(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Initialize(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath);
    void Initialize(const GLchar* computePath);
    void Release();

    void Use();
    GLuint GetProgram() const {
        return program;
    }
    
    GLuint program;
private:

};
