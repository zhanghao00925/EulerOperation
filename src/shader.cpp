#include "shader.hpp"
// STL
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Shader::Initialize(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_ERROR" << endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "IN: " << vertexPath << " and " << fragmentPath << endl;
        cout << "ERROR::SHADER::VERTEX_COMPILE\n"
             << infoLog << endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "IN: " << vertexPath << " and " << fragmentPath << endl;
        cout << "ERROR::SHADER::FRAGMENT_COMPILE\n"
             << infoLog << endl;
    }
    glUseProgram(program);
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "IN: " << vertexPath << " and " << fragmentPath << endl;
        cout << "ERROR::SHADER::PROGRAM_LINK\n"
             << infoLog << endl;
    };

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Initialize(const GLchar *vertexPath, const GLchar *geometryPath, const GLchar *fragmentPath)
{
    string vertexCode;
    string geometryCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream gShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::badbit);
    gShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        gShaderFile.open(geometryPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, gShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        gShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        geometryCode = gShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_ERROR" << endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment, geometry;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "IN: " << vertexPath << endl;
        cout << "ERROR::SHADER::VERTEX_COMPILE\n"
             << infoLog << endl;
    }

    // Geometry Shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry, 512, NULL, infoLog);
        cout << "IN: " << geometryPath << endl;
        cout << "ERROR::SHADER::GEOMETRY_COMPILE\n"
             << infoLog << endl;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "IN: " << fragmentPath << endl;
        cout << "ERROR::SHADER::FRAGMENT_COMPILE\n"
             << infoLog << endl;
    }
    glUseProgram(program);
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, geometry);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "IN: " << vertexPath << " and " << geometryPath << " and "<< fragmentPath << endl;
        cout << "ERROR::SHADER::PROGRAM_LINK\n"
             << infoLog << endl;
    };

    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);
}

void Shader::Initialize(const GLchar *computePath)
{
    string computeCode;
    ifstream cShaderFile;

    cShaderFile.exceptions(ifstream::badbit);

    try
    {
        cShaderFile.open(computePath);

        stringstream vShaderStream, fShaderStream;
        vShaderStream << cShaderFile.rdbuf();

        cShaderFile.close();

        computeCode = vShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_ERROR" << endl;
    }

    const GLchar *cShaderCode = computeCode.c_str();

    GLuint compute;
    GLint success;
    GLchar infoLog[512];

    compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cShaderCode, NULL);
    glCompileShader(compute);
    glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(compute, 512, NULL, infoLog);
        cout << "IN: " << computePath << endl;
        cout << "ERROR::SHADER::COMPUTE_COMPILE\n"
             << infoLog << endl;
    }
    glUseProgram(program);
    program = glCreateProgram();
    glAttachShader(program, compute);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "IN: " << computePath << endl;
        cout << "ERROR::SHADER::PROGRAM_LINK\n"
             << infoLog << endl;
    };

    glDeleteShader(compute);
}

void Shader::Use()
{
    glUseProgram(program);
}

void Shader::Release()
{
    glDeleteProgram(program);
}